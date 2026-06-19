#pragma once
#include "database.h"

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

private:
    void getTask(int argc, char** argv);
    void makeCalculate();
    void printResult() const;

private:
    Task task_;
    DataBase dataBase_;
};

} // namespace calculator
