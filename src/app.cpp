#include "app.h"
#include "libmath.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
    for (int i = 1; i < argc; i++)
    {
        if (std::strcmp(argv[i], "-h") == 0 || std::strcmp(argv[i], "--help") == 0)
            return false;
    }
    if (argc != 4)
        return false;
    task.value1    = std::atoi(argv[1]);
    task.operation = argv[2][0];
    task.value2    = std::atoi(argv[3]);
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
