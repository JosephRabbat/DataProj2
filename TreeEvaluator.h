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
	ListStack<char>* numberStack; // stack used to read digits and convert them to numbers
    bool isOperator(char c) const; // returns 1 if char is an operator 
    double stringToDouble(const std::string str) const; // converts a string to a double
    int precedence(char op) const; // checks the precedence value of an operator
public:
    TreeEvaluator() { expressionTree = new binaryTree<std::string>; numberStack = new ListStack<char>; } // constructor
    void buildExpressionTree(std::string expression) throw(SyntaxError); // function to build the expression tree
    double evaluateTree(Position<std::string>* p) throw(MathError); // function to evaluate the tree
    Position<std::string>* getRoot() { return expressionTree->getRoot(); } // returns root of tree
    void destroy() { expressionTree->~binaryTree(); expressionTree = new binaryTree<std::string>; } // destroys the tree
};

