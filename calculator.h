#pragma once
#include <string>

class Calculator
{
public:
Calculator(const std::string& json);

int calculate();

private:
int value1{};
char operation {};
int value2{};
};