#pragma once
#include "SyntaxError.h"
#include "MathError.h"
#include "binaryTree.h"
#include "ListStack.h"
#include <sstream>

class TreeEvaluator
{
private:
	binaryTree<std::string>* expressionTree;
	ListStack<char>* numberStack;
    bool isOperator(char c) const;
    double stringToDouble(const std::string str) const;
    int precedence(char op) const;
public:
    TreeEvaluator() { expressionTree = new binaryTree<std::string>; numberStack = new ListStack<char>; }
    void buildExpressionTree(std::string expression) throw(SyntaxError);
    double evaluateTree(Position<std::string>* p) throw(MathError);
    Position<std::string>* getRoot() { return expressionTree->getRoot(); }
    void destroy() { expressionTree->~binaryTree(); expressionTree = new binaryTree<std::string>; }
    void print() { expressionTree->print(); }
};

