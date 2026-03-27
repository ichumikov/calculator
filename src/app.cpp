#include "app.h"
#include "libmath.h"
#include <cstdlib>
#include <iostream>
struct Task
{
    int value1{};
    char operation{};
    int value2{};
    int status{};
    int result{};
};
static void parse(int argc, char** argv, Task& task)
{
    task.value1 = std::atoi(argv[1]);
    task.operation = argv[2][0];
    task.value2 = std::atoi(argv[3]);
}
static void calculate(Task& task)
{
    switch (task.operation)
    {
    case '+':
        task.status = math::addition(task.value1, task.value2, task.result);
        break;
    case '-':
        task.status = math::subtraction(task.value1, task.value2, task.result);
        break;
    case '*':
        task.status = math::multiplication(task.value1, task.value2, task.result);
        break;
    case '/':
        task.status = math::division(task.value1, task.value2, task.result);
        break;
    case '^':
        task.status = math::power(task.value1, task.value2, task.result);
        break;
    case '!':
        task.status = math::factorial(task.value1, task.result);
        break;
    default:
        task.status = 1;
        break;
    }
}
static void output(const Task& task)
{
    if (task.status == 0)
    {
        std::cout << task.value1 << ' ' << task.operation << ' ' << task.value2
                  << " = " << task.result << '\n';
    }
    else if (task.status == -1)
    {
        std::cout << "Error! Division by zero!\n";
    }
    else if (task.status == -2)
    {
        std::cout << "Error! Factorial for negative number!\n";
    }
    else if (task.status == -3)
    {
        std::cout << "Error! Integer overflow!\n";
    }
    else if (task.status == -4)
    {
        std::cout << "Error! Negative power is not supported for integer result!\n";
    }
    else if (task.status == 1)
    {
        std::cout << "Error! Unknown operation!\n";
    }
    else
    {
        std::cout << "Unknown error\n";
    }
}
namespace app
{
void run(int argc, char** argv)
{
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <value1> <op> <value2>\n";
        std::cerr << "Examples:\n";
        std::cerr << "  " << argv[0] << " 2 + 3\n";
        std::cerr << "  " << argv[0] << " 5 ! 0\n";
        return;
    }
    Task task;
    parse(argc, argv, task);
    calculate(task);
    output(task);
}
}
