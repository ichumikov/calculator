#include "app.h"
#include <gtest/gtest.h>

class ApplicationTest : public ::testing::Test
{
protected:
    int runApp(const char* json)
    {
        const char* argv[] = {"calculator", json};
        calculator::Application app;
        return app.run(2, const_cast<char**>(argv));
    }
};

TEST_F(ApplicationTest, Addition)
{
    EXPECT_EQ(runApp(R"({"a": 10, "op": "+", "b": 5})"), 0);
}

TEST_F(ApplicationTest, Subtraction)
{
    EXPECT_EQ(runApp(R"({"a": 10, "op": "-", "b": 3})"), 0);
}

TEST_F(ApplicationTest, Multiplication)
{
    EXPECT_EQ(runApp(R"({"a": 5, "op": "*", "b": 4})"), 0);
}

TEST_F(ApplicationTest, Division)
{
    EXPECT_EQ(runApp(R"({"a": 10, "op": "/", "b": 2})"), 0);
}

TEST_F(ApplicationTest, Factorial)
{
    EXPECT_EQ(runApp(R"({"a": 5, "op": "!"})"), 0);
}

TEST_F(ApplicationTest, DivisionByZero)
{
    EXPECT_NE(runApp(R"({"a": 10, "op": "/", "b": 0})"), 0);
}

TEST_F(ApplicationTest, UnknownOperation)
{
    EXPECT_NE(runApp(R"({"a": 10, "op": "?", "b": 5})"), 0);
}

TEST_F(ApplicationTest, NegativeFactorial)
{
    EXPECT_NE(runApp(R"({"a": -5, "op": "!"})"), 0);
}