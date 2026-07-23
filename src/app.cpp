#include "app.h"
#include "libmath.h"
#include "logger.h"
#include <cstdio>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <csignal>
#include <pthread.h>
#include <chrono>

namespace calculator {

Application::Application() : server_(io_, 8080, running_)
{
    dataBase_.connect();
    dataBase_.warmUpCache();
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGTERM);
    pthread_sigmask(SIG_BLOCK, &sigset, nullptr);
    signalThread_ = std::thread(&Application::runSignalHandler, this);
    serverThread_ = std::thread(&Server::run, &server_);
}

Application::~Application()
{
    dataBase_.disconnect();
    if(signalThread_.joinable())
        signalThread_.join();
    if(serverThread_.joinable())
        serverThread_.join();
}
int Application::run(int argc, char** argv)
{
    if (argc < 2) {
        while (running_) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        return 0;
    }

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

void Application::calculate(Task& task)
{
    switch (task.operation) {
        case '+':
            task.result = math::addition(task.firstValue, task.secondValue);
            break;
        case '-':
            task.result = math::subtraction(task.firstValue, task.secondValue);
            break;
        case '*':
            task.result = math::multiplication(task.firstValue, task.secondValue);
            break;
        case '/':
            task.result = math::division(task.firstValue, task.secondValue);
            break;
        case '^':
            task.result = math::power(task.firstValue, task.secondValue);
            break;
        case '!':
            task.result = math::factorial(task.firstValue);
            break;
        default:
            throw std::invalid_argument("Unknown operation");
            break;
        } 
}

void Application::makeCalculate()
{
    calculate(task_);
}

void Application::printResult() const
{
    if (task_.operation == '!') {
        printf("%d! = %d\n", task_.firstValue, task_.result);
    } else {
        printf("%d %c %d = %d\n", task_.firstValue, task_.operation, task_.secondValue, task_.result);
    }
}

void Application::runSignalHandler()
{
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGTERM);
    int sig = 0;
    sigwait(&sigset, &sig);
    running_ = false;
}

} // namespace calculator
