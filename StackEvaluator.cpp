#include "StackEvaluator.h"

bool StackEvaluator::isOperator(char c) const
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

double StackEvaluator::stringToDouble(const std::string str) const
{
    return std::stod(str);
}

int StackEvaluator::precedence(char op) const
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

StackEvaluator::StackEvaluator()
{
    valueStack = new ListStack<double>;
    opStack = new ListStack<char>;
    numberStack = new ListStack<char>;
}

double StackEvaluator::evaluate(std::string expression)
{
    while (!valueStack->empty()) valueStack->pop();
    while (!opStack->empty()) opStack->pop();

    std::istringstream iss(expression);
    char token, prevToken = '\0'; // Initialize prevToken to a non-operator value
    bool prevTokenIsOperator = false;

    while (iss >> token) {
        if ((std::isdigit(token) || token == '.')) {
            // Operand, push onto the number stack
            numberStack->push(token);
            prevTokenIsOperator = false;
        }
        else if (isOperator(token)) {
            if (prevTokenIsOperator || prevToken == '\0') {
                // Two consecutive operators or operator at the beginning
                throw SyntaxError();
            }

            // Operator, pop and evaluate until the stack is empty or top has lower precedence
            std::string temp = "";
            while (!numberStack->empty())
            {
                temp = numberStack->top() + temp;
                numberStack->pop();
            }
            valueStack->push(stringToDouble(temp));

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
                    case '/':
                        if (right == 0) {
                            throw MathError();
                        }
                        valueStack->push(left / right);
                        break;
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
            prevTokenIsOperator = true;
        }
        prevToken = token;
    }

    // Check for operator at the end
    if (prevTokenIsOperator) {
        throw SyntaxError();
    }

    std::string temp = "";
    while (!numberStack->empty())
    {
        temp = numberStack->top() + temp;
        numberStack->pop();
    }
    valueStack->push(stringToDouble(temp));

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
        case '/':
            if (right == 0) {
                throw MathError();
            }
            valueStack->push(left / right);
            break;
        default: break; // Invalid operator
        }
    }
    // The final result should be on the top of the value stack

    return valueStack->top();
}

