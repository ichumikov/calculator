#pragma once

namespace calculator
{

class Application
{
  public:
    int run(int argc, char** argv);

  private:
    void getTask(int argc, char** argv);
    void makeCalculate();
    void printResult() const;
 
  private:
    struct Task
    {
        int firstValue;
        int secondValue;
        char operation;
        int result;
        int status;
    };

  private:
    Task task_;
};

} //namespace calculator

