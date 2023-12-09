#pragma once
#include "SyntaxError.h"
#include "MathError.h"
#include "ListStack.h"
#include <sstream>

class StackEvaluator
{
private:
    ListStack<double>* valueStack;
    ListStack<char>* opStack;
    ListStack<char>* numberStack;
    bool isOperator(char c) const;
    double stringToDouble(const std::string str) const;
    int precedence(char op) const;
public:
    StackEvaluator();
    double evaluate(std::string expression) throw (SyntaxError, MathError);
};

