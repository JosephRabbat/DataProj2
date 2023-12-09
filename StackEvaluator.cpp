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
    while (!valueStack->empty()) valueStack->pop(); // empty the value stack before starting
    while (!opStack->empty()) opStack->pop(); // empty the operation stack before starting

    std::istringstream iss(expression);
    char token, prevToken = '\0'; // Initialize prevToken to a non-operator value
    bool prevTokenIsOperator = false; // bool to know if the previous token was already an operator

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

            std::string temp = "";
            while (!numberStack->empty()) // empty the number stack
            {
                temp = numberStack->top() + temp; // add all chars of the number stack to the temp string
                numberStack->pop();
            }
            valueStack->push(stringToDouble(temp)); // convert the temp string to a double value and push it to the value stack

            if (!opStack->empty())
            {
                while (precedence(opStack->top()) >= precedence(token)) // keep looping until precedence of token is higher
                {
                    char op = opStack->top(); // get the operation to perform
                    opStack->pop();
                    double right = valueStack->top(); // get the right value
                    valueStack->pop();
                    double left = valueStack->top(); // get the left value
                    valueStack->pop();
                    // Perform operation and push result back to the value stack
                    switch (op) {
                    case '+': valueStack->push(left + right); break;
                    case '-': valueStack->push(left - right); break;
                    case '*': valueStack->push(left * right); break;
                    case '/':
                        if (right == 0) {
                            throw MathError(); // throw exception when dividing by 0
                        }
                        valueStack->push(left / right);
                        break;
                    default: break; // Invalid operator
                    }
                    if (opStack->empty())
                    {
                        break; // stop if opStack is empty
                    }
                }
            }
            // Push the current operator onto the operator stack
            opStack->push(token);
            prevTokenIsOperator = true; // set the bool to true since the previous token was an operator
        }
        prevToken = token; // set prevToken to token
    }

    // Check for operator at the end
    if (prevTokenIsOperator) {
        throw SyntaxError(); // throw syntax error if last token is an operator
    }

    std::string temp = "";
    while (!numberStack->empty()) // empty the number stack
    {
        temp = numberStack->top() + temp; // add all chars of the number stack to the temp string
        numberStack->pop();
    }
    valueStack->push(stringToDouble(temp)); // convert the temp string to a double value and push it to the value stack

    // Process remaining operators
    while (!opStack->empty()) {
        char op = opStack->top(); // get the operation to perform
        opStack->pop();
        double right = valueStack->top(); // get the right value
        valueStack->pop();
        double left = valueStack->top(); // get the left value
        valueStack->pop();
        // Perform operation and push result back to the value stack
        switch (op) {
        case '+': valueStack->push(left + right); break;
        case '-': valueStack->push(left - right); break;
        case '*': valueStack->push(left * right); break;
        case '/':
            if (right == 0) {
                throw MathError(); // throw exception when dividing by 0
            }
            valueStack->push(left / right);
            break;
        default: break; // Invalid operator
        }
    }
    // The final result should be on the top of the value stack

    return valueStack->top();
}

