#include "calculator.h"
#include <iostream>
#include <stdexcept>

int main(int argc, char** argv)
{
if (argc != 2)
{
    std::cerr<< "not or many arguments";
    return 1;
}
try
{
    Calculator calc(argv[1]);  
    int result = calc.calculate(); 
    std::cout << result << "\n";  
}
catch (const std::exception& e)
{
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
}
}
