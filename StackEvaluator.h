#pragma once
#include "SyntaxError.h"
#include "MathError.h"
#include "ListStack.h"
#include <sstream>

class StackEvaluator
{
private:
    ListStack<double>* valueStack; // stack holding values of computation
    ListStack<char>* opStack; // stack holding operations of computation
    ListStack<char>* numberStack; // stack used to read digits and convert them to numbers
    bool isOperator(char c) const; // returns 1 if char is an operator
    double stringToDouble(const std::string str) const; // converts a string to a double
    int precedence(char op) const; // checks the precedence value of an operator
public:
    StackEvaluator(); // constructor
    double evaluate(std::string expression) throw (SyntaxError, MathError); // evaluate the expression
};

