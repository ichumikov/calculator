#include <gtest/gtest.h>
#include "calculator.h"

TEST(CalculatorTest, Addition)
{
    Calculator calc("{\"a\": 10, \"op\": \"+\", \"b\": 5}");
    EXPECT_EQ(calc.calculate(), 15);
}

TEST(CalculatorTest, Subtraction)
{
    Calculator calc("{\"a\": 10, \"op\": \"-\", \"b\": 3}");
    EXPECT_EQ(calc.calculate(), 7);
}

TEST(CalculatorTest, Multiplication)
{
    Calculator calc("{\"a\": 5, \"op\": \"*\", \"b\": 4}");
    EXPECT_EQ(calc.calculate(), 20);
}

TEST(CalculatorTest, Division)
{
    Calculator calc("{\"a\": 10, \"op\": \"/\", \"b\": 2}");
    EXPECT_EQ(calc.calculate(), 5);
}

TEST(CalculatorTest, Factorial)
{
    Calculator calc("{\"a\": 5, \"op\": \"!\"}");
    EXPECT_EQ(calc.calculate(), 120);
}

TEST(CalculatorTest, DivisionByZero)
{
    Calculator calc("{\"a\": 10, \"op\": \"/\", \"b\": 0}");
    EXPECT_THROW(calc.calculate(), std::domain_error);
}

TEST(CalculatorTest, UnknownOperation)
{
    Calculator calc("{\"a\": 10, \"op\": \"?\", \"b\": 5}");
    EXPECT_THROW(calc.calculate(), std::invalid_argument);
}

TEST(CalculatorTest, NegativeFactorial)
{
    Calculator calc("{\"a\": -5, \"op\": \"!\"}");
    EXPECT_THROW(calc.calculate(), std::domain_error);
}