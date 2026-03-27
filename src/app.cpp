#include "app.h"
#include "libmath.h"
#include <cstdio>
#include <cstdlib>
#include <getopt.h>
struct Task
{
    int value1{};
    char operation{};
    int value2{};
    int status{};
    int result{};
};
static bool parse(int argc, char** argv, Task& task)
{
    static const option long_options[] = {
        {"help", no_argument, nullptr, 'h'},
        {nullptr, 0,          nullptr,  0 }
    };
    int opt;
    while ((opt = getopt_long(argc, argv, "+h", long_options, nullptr)) != -1)
    {
        if (opt == 'h')
            return false;
    }
    if (argc - optind != 3)
        return false;
    task.value1    = std::atoi(argv[optind]);
    task.operation = argv[optind + 1][0];
    task.value2    = std::atoi(argv[optind + 2]);
    return true;
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
        printf("%d %c %d = %d\n", task.value1, task.operation, task.value2, task.result);
    }
    else if (task.status == -1)
    {
        printf("Error! Division by zero!\n");
    }
    else if (task.status == -2)
    {
        printf("Error! Factorial for negative number!\n");
    }
    else if (task.status == -3)
    {
        printf("Error! Integer overflow!\n");
    }
    else if (task.status == -4)
    {
        printf("Error! Negative power is not supported for integer result!\n");
    }
    else if (task.status == 1)
    {
        printf("Error! Unknown operation!\n");
    }
    else
    {
        printf("Unknown error\n");
    }
}
namespace app
{
void run(int argc, char** argv)
{
    Task task;
    if (!parse(argc, argv, task))
    {
        fprintf(stderr, "Usage: %s <value1> <op> <value2>\n", argv[0]);
        fprintf(stderr, "\nOperations:\n");
        fprintf(stderr, "  +     addition        %s 2 + 3\n", argv[0]);
        fprintf(stderr, "  -     subtraction     %s 10 - 4\n", argv[0]);
        fprintf(stderr, "  '*'   multiplication  %s 3 '*' 7\n", argv[0]);
        fprintf(stderr, "  /     division        %s 10 / 2\n", argv[0]);
        fprintf(stderr, "  '^'   power           %s 2 '^' 8\n", argv[0]);
        fprintf(stderr, "  '!'   factorial       %s 5 '!' 0\n", argv[0]);
        fprintf(stderr, "\nNote: *, ^, ! are shell special characters and must be quoted.\n");
        fprintf(stderr, "      For factorial, value2 is ignored.\n");
        return;
    }
    calculate(task);
    output(task);
}
}
