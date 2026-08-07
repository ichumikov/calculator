#pragma once
#include "database.h"
#include <atomic>
#include <thread>
#include "server.h"
#include <boost/asio.hpp>

namespace calculator {

class Application {

public:
    Application();
    ~Application();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(Application&&) = delete;
    int run(int argc, char** argv);
    static void calculate(Task& task);

private:
    void getTask(int argc, char** argv);
    void makeCalculate();
    void printResult() const;
    std::atomic<bool> running_{true};
    std::thread signalThread_;
    void runSignalHandler();
    Task task_;
    DataBase dataBase_;
    boost::asio::io_context io_;
    Server server_;
    std::thread serverThread_;
};

} // namespace calculator
