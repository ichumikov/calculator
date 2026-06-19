#include "app.h"
#include "libmath.h"
#include "logger.h"
#include <cstdio>
#include <nlohmann/json.hpp>
#include <stdexcept>

namespace calculator {

Application::Application()
{
    dataBase_.connect();
    dataBase_.warmUpCache();
}

Application::~Application()
{
    dataBase_.disconnect();
}
int Application::run(int argc, char** argv)
{
    try {
        getTask(argc, argv);
        std::optional<Task> cached = dataBase_.getRecord(task_);
        if (!cached) {
            makeCalculate();
            dataBase_.writeRecord(task_);
        } else {
            task_ = *cached;
        }
        printResult();
        task_.status = 0;
    } catch (const std::exception& e) {
        Logger::instance().error(e.what());
        task_.status = 1;
    }
    return task_.status;
}

void Application::getTask(int argc, char** argv)
{
    auto j = nlohmann::json::parse(argv[1]);

    task_.firstValue = j["a"];
    std::string op = j["op"];
    task_.operation = op[0];
    if (j.contains("b")) {
        task_.secondValue = j["b"];
    }
}

void Application::makeCalculate()
{
    switch (task_.operation) {
    case '+':
        task_.result = math::addition(task_.firstValue, task_.secondValue);
        break;
    case '-':
        task_.result = math::subtraction(task_.firstValue, task_.secondValue);
        break;
    case '*':
        task_.result = math::multiplication(task_.firstValue, task_.secondValue);
        break;
    case '/':
        task_.result = math::division(task_.firstValue, task_.secondValue);
        break;
    case '^':
        task_.result = math::power(task_.firstValue, task_.secondValue);
        break;
    case '!':
        task_.result = math::factorial(task_.firstValue);
        break;
    default:
        throw std::invalid_argument("Unknown operation");
        break;
    }
}

void Application::printResult() const
{
    if (task_.operation == '!') {
        printf("%d! = %d\n", task_.firstValue, task_.result);
    } else {
        printf("%d %c %d = %d\n", task_.firstValue, task_.operation, task_.secondValue, task_.result);
    }
}

} // namespace calculator
