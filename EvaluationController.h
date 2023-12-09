#pragma once
#include <string>
#include "TreeEvaluator.h"
#include "StackEvaluator.h"

class EvaluationController {
private:
    TreeEvaluator Tree;
    StackEvaluator Stacks;
    std::string expression;

    void destroyExpressionTree();
public:
    void setExpression(std::string expr);
    EvaluationController();
    ~EvaluationController();
    double evaluateUsingTree();
    void printExpressionTree();
    double evaluateUsingStacks();
};