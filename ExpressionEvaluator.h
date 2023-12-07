#pragma once
#include <string>
#include "ListStack.h"
#include "binaryTree.h"
#include <sstream>
#include <cctype>

class ExpressionEvaluator {
private:
    binaryTree<std::string>* expressionTree;
    ListStack<double>* valueStack;
    ListStack<char>* opStack;
    std::string expression;

    bool isOperator(char c) const;
    double stringToDouble(const std::string& str) const;
    Position<std::string>* buildExpressionTree();
    double evaluateTree(Position<std::string>* p);
    int precedence(char op) const;

public:
    void setExpression(std::string expr);
    ExpressionEvaluator();
    ~ExpressionEvaluator();
    double evaluateUsingTree();
    void destroyExpressionTree();
    void printExpressionTree();
    double evaluateUsingStacks();
    
};