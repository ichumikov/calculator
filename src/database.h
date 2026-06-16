#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <optional>
#include <libpq-fe.h>
#include <cstdint>

namespace calculator
{

struct Task
{
    int firstValue{0};
    int secondValue{0};
    char operation{'\0'};
    int result{0};
    int status{0};
};

class DataBase
{
public:
    struct Config
    {
        std::string host{"localhost"};
        std::uint16_t port{5432};
        std::string username {"postgres"};
        std::string password{"postgres"};
        std::string dbname{"calculator_db"};
    };

    DataBase();
    ~DataBase();

    void connect();
    void disconnect();
    void warmUpCache();

    std::optional<Task> getRecord(const Task& task);
    void writeRecord(const Task& task);

private:
    std::string makeKey(const Task& task) const;

private:
    Config config_;
    std::unique_ptr<PGconn, decltype(&PQfinish)> connection_{nullptr, PQfinish};
    std::unordered_map<std::string, Task> cache_;
};

} // namespace calculator