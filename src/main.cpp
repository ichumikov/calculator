#include "calculator.h"
#include "logger.h"
#include <iostream>
#include <stdexcept>

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "not or many arguments";
        return 1;
    }
    try {
        Logger::instance().info("Starting calculation");
        Calculator calc(argv[1]);
        int result = calc.calculate();
        Logger::instance().info("Result: " + std::to_string(result));
        std::cout << result << "\n";
    } catch (const std::exception& e) {
        Logger::instance().error(e.what());
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
