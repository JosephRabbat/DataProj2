#include "ExpressionEvaluator.h"

bool ExpressionEvaluator::isOperator(char c) const
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

double ExpressionEvaluator::stringToDouble(const std::string& str) const
{
    return std::stod(str);
}

Position<std::string>* ExpressionEvaluator::buildExpressionTree()
{

    std::istringstream iss(expression);
    ListStack<Position<std::string>*> nodes;
    ListStack<char> operators;
    char token;
    while (iss >> token) {
        Position<std::string>* newNode = new Position<std::string>;
        newNode->setElem(std::string(1, token));
        if (!isOperator(token)) {
            nodes.push(newNode);
        }
        else {
            if (!operators.empty())
            {
                while (precedence(operators.top()) >= precedence(token)) {
                    Position<std::string>* newNode2 = new Position<std::string>;
                    newNode2->setElem(std::string(1, operators.top()));
                    newNode2->right = nodes.top();
                    nodes.pop();
                    newNode2->left = nodes.top();
                    nodes.pop();
                    nodes.push(newNode2);
                    operators.pop();
                    if (operators.empty())
                    {
                        break;
                    }
                }
            }
            operators.push(token);
        }
    }
    while (!operators.empty()) {
        Position<std::string>* newNode = new Position<std::string>;
        newNode->setElem(std::string(1, operators.top()));
        newNode->right = nodes.top();
        nodes.pop();
        newNode->left = nodes.top();
        nodes.pop();
        nodes.push(newNode);
        operators.pop();
    }
    return nodes.top();

}

double ExpressionEvaluator::evaluateTree(Position<std::string>* p)
{

    if (p->isExternal()) {
        return stringToDouble(p->getElem()); // Leaf node (operand)
    }
    double leftValue = evaluateTree(p->getLeft());
    double rightValue = evaluateTree(p->getRight());
    char op = p->getElem()[0];
    switch (op) {
    case '+': return leftValue + rightValue;
    case '-': return leftValue - rightValue;
    case '*': return leftValue * rightValue;
    case '/': return leftValue / rightValue; // Assuming rightValue is not 0
    default: return 0; // Invalid operator
    }

}

int ExpressionEvaluator::precedence(char op) const
{

    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;

}

void ExpressionEvaluator::setExpression(std::string expr)
{
    expression = expr;
}

ExpressionEvaluator::ExpressionEvaluator()
{
    expressionTree = new binaryTree<std::string>; valueStack = new ListStack<double>; opStack = new ListStack<char>;
}

ExpressionEvaluator::~ExpressionEvaluator()
{
    destroyExpressionTree(); delete valueStack; delete opStack;
}

double ExpressionEvaluator::evaluateUsingTree()
{
    expressionTree->root = buildExpressionTree(); return evaluateTree(expressionTree->getRoot());
}

void ExpressionEvaluator::destroyExpressionTree()
{
    expressionTree->destroy();
}

void ExpressionEvaluator::printExpressionTree()
{
    expressionTree->print();
}

double ExpressionEvaluator::evaluateUsingStacks()
{

    while (!valueStack->empty()) valueStack->pop();
    while (!opStack->empty()) opStack->pop();

    std::istringstream iss(expression);
    char token;
    while (iss >> token) {
        if (std::isdigit(token)) {
            // Operand, push onto the value stack
            double operand = static_cast<double>(token - '0');
            valueStack->push(operand); // Convert char to integer
        }
        else if (isOperator(token)) {
            // Operator, pop and evaluate until the stack is empty or top has lower precedence

            if (!opStack->empty())
            {
                while (precedence(opStack->top()) >= precedence(token))
                {
                    char op = opStack->top();
                    opStack->pop();
                    double right = valueStack->top();
                    valueStack->pop();
                    double left = valueStack->top();
                    valueStack->pop();
                    // Perform operation and push result back to the value stack
                    switch (op) {
                    case '+': valueStack->push(left + right); break;
                    case '-': valueStack->push(left - right); break;
                    case '*': valueStack->push(left * right); break;
                    case '/': valueStack->push(left / right); break; // Assuming right is not 0
                    default: break; // Invalid operator
                    }
                    if (opStack->empty())
                    {
                        break;
                    }
                }
            }
            // Push the current operator onto the operator stack
            opStack->push(token);
        }
    }

    // Process remaining operators
    while (!opStack->empty()) {
        char op = opStack->top();
        opStack->pop();
        double right = valueStack->top();
        valueStack->pop();
        double left = valueStack->top();
        valueStack->pop();
        // Perform operation and push result back to the value stack
        switch (op) {
        case '+': valueStack->push(left + right); break;
        case '-': valueStack->push(left - right); break;
        case '*': valueStack->push(left * right); break;
        case '/': valueStack->push(left / right); break; // Assuming right is not 0
        default: break; // Invalid operator
        }
    }
    // The final result should be on the top of the value stack

    return valueStack->top();

}
