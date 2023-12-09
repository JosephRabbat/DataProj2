#pragma once
#include <string>
#include "TreeEvaluator.h"
#include "StackEvaluator.h"

class EvaluationController {
private:
    TreeEvaluator Tree;
    StackEvaluator Stacks;
    std::string expression;

    void destroyExpressionTree(); // function to destroy the tree
public:
    void setExpression(std::string expr); // function to set the expression string
    EvaluationController(); // constructor
    ~EvaluationController(); // destructor
    double evaluateUsingTree(); // function to evaluate the expression using the tree
    double evaluateUsingStacks(); // function to evaluate the expression using stacks
};