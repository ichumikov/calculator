#include "calculator.h"
#include <nlohmann/json.hpp>
#include "libmath.h"
#include <stdexcept>

Calculator::Calculator(const std::string& json)
{
    auto j = nlohmann::json::parse(json);
    value1 = j["a"];
    std::string op = j["op"];
    operation = op[0];
    if (j.contains("b"))
    {
        value2 = j["b"];
    }
}

int Calculator::calculate()
{
    switch(operation)
    {
        case '+':
        return math::addition(value1, value2);
        case '-':
        return math::subtraction(value1, value2);
        case '*':
        return math::multiplication(value1, value2);
        case '/':
        return math::division(value1, value2);
        case '^':
        return math::power(value1, value2);
        case '!':
        return math::factorial(value1);
        default: throw std::invalid_argument("unknown argument");
    }
}