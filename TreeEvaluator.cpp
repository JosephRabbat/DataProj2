#include "TreeEvaluator.h"

int TreeEvaluator::precedence(char op) const
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

double TreeEvaluator::evaluateTree(Position<std::string>* p)
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
    case '/': 
        if (rightValue == 0)
        {
            throw MathError();
        }
        return leftValue / rightValue;
    default: return 0; // Invalid operator
    }
}

void TreeEvaluator::buildExpressionTree(std::string expression)
{
    destroy();

    if (isOperator(expression[0]) || isOperator(expression.back())) {
        throw SyntaxError();
    }

    std::istringstream iss(expression);
    ListStack<Position<std::string>*> nodes;
    ListStack<char> operators;
    char token, prevToken = '\0';

    // Process all characters except the last one
    while (iss.get(token)) {
        if (!isOperator(token)) {
            if (std::isdigit(token) || token == '.') {
                // Operand, push onto the number stack
                numberStack->push(token);
            }
        }
        else {
            // Check for two consecutive operators
            if (isOperator(prevToken)) {
                throw SyntaxError();
            }

            Position<std::string>* temp = new Position<std::string>;
            temp->elem = "";
            while (!numberStack->empty())
            {
                temp->elem = numberStack->top() + temp->elem;
                numberStack->pop();
            }
            nodes.push(temp);
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

        // Update prevToken for the next iteration
        prevToken = token;
    }

    // Check for consecutive operators
    if (isOperator(prevToken) || isOperator(token)) {
        throw SyntaxError();
    }

    // Process any remaining operands
    Position<std::string>* temp = new Position<std::string>;
    temp->elem = "";
    while (!numberStack->empty())
    {
        temp->elem = numberStack->top() + temp->elem;
        numberStack->pop();
    }
    nodes.push(temp);

    // Process remaining operators
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
    expressionTree->root = nodes.top();
}



bool TreeEvaluator::isOperator(char c) const
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

double TreeEvaluator::stringToDouble(const std::string str) const
{
    return std::stod(str);
}