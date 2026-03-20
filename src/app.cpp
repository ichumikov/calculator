#include "app.h"
#include "math.h"

#include <iostream>
using namespace math;

struct Task
{
	int value1;
	char operation;
	int value2;
	int status;
	int result;
};

void parse(int argc, char** argv, Task& task)
{
	task.value1 = std::atoi(argv[1]);
	task.operation = *(argv[2]);
	task.value2 = std::atoi(argv[3]);
}

void calculate(Task& task)
{
	task.status = 0;
	switch(task.operation)
	{
		case '+':
	        task.result = addition(task.value1, task.value2);
	        break;
	        case '-':
	        task.result = subtraction(task.value1, task.value2);
	        break;
	        case '*':
	        task.result = multiplication(task.value1, task.value2);
	        break;
	        case '/':
	        task.status = division(task.value1, task.value2, task.result);
	        break;
	        case '^':                                   
		task.result = power(task.value1, task.value2);
	        break;
		case '!':
		task.status = factorial(task.value1, task.result);
		break;
		default:
			task.status = 1;
	}
}

void output(Task task)
{
        if (task.status == 0)
        {
                std::cout << task.value1 << ' ' << task.operation << ' ' << task.value2 << " = " << task.result << '\n';
        }
	        else if (task.status == -1)
        {
                std::cout << "Error! Division by zero!\n";
        }
	        else if (task.status == 1)
        {
                std::cout << "Error! Unknown operation!\n";
        }
	        else if (task.status == -2)
        {
                std::cout << "Error! Factorial for negative number!\n";
        }
	        else
        {
                std::cout << "Unknown error\n";
        }
}
void run(int argc, char** argv)
{
        Task task;
        parse(argc, argv, task);
        calculate(task);
        output(task);
}

