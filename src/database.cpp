#include "database.h"
#include <stdexcept>
#include <string>

namespace calculator
{
    DataBase::DataBase() = default;

    DataBase::~DataBase()
    {
        disconnect();
    }

    void DataBase::connect() 
    {
        std::string connStr = "host=" + config_.host + " port=" + std::to_string(config_.port)
        +" user=" + config_.username + " password=" + config_.password + " dbname=" + config_.dbname;

        connection_.reset(PQconnectdb(connStr.c_str()));
        if (PQstatus(connection_.get()) != CONNECTION_OK)
        {
            throw std::runtime_error(PQerrorMessage(connection_.get()));
        }
    }

    void DataBase::disconnect()
    {
        connection_.reset();
    }
    std::string DataBase::makeKey(const Task& task) const
    {
        int first = task.firstValue;
        int second = task.secondValue;
        if ((task.operation == '+' || task.operation == '*') && (first > second))
        {
            std::swap(first, second);
        }
        return std::to_string(first) + task.operation + std::to_string(second);
    }

    void DataBase::warmUpCache()
    {
        std::unique_ptr<PGresult, decltype(&PQclear)>res(
            PQexec(connection_.get(), "SELECT first_value, second_value, operation, result, status FROM calculations"),
            PQclear
        );

        int rows = PQntuples(res.get());
        for (int i = 0; i < rows; i++)
        {
            Task task;
            task.firstValue = std::atoi(PQgetvalue(res.get(), i, 0));
            task.secondValue = std::atoi(PQgetvalue(res.get(), i, 1));
            task.operation = PQgetvalue(res.get(), i, 2)[0];
            task.result = std::atoi(PQgetvalue(res.get(), i, 3));
            task.status = std::atoi(PQgetvalue(res.get(), i, 4));

            cache_[makeKey(task)] = task;
        }
    }
    std::optional<Task> DataBase::getRecord(const Task& task)
    {
        std::string key = makeKey(task);
        if(cache_.count(key) > 0)
        {
            return cache_[key];
        }
        return std::nullopt;    
    }

    void DataBase::writeRecord(const Task& task) 
    {
        std::string sql = "INSERT INTO calculations (first_value, second_value, operation, result, status) VALUES (" +
        std::to_string(task.firstValue) + ", " +
        std::to_string(task.secondValue) + ", '" +
        task.operation + "', " +
        std::to_string(task.result) + ", " +
        std::to_string(task.status) + ")";

        std::unique_ptr<PGresult, decltype(&PQclear)> res(
            PQexec(connection_.get(), sql.c_str()),
            PQclear
        );    
            cache_[makeKey(task)] = task;
    }   
    
} // namespace calculator