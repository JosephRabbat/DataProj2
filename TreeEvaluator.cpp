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
    double leftValue = evaluateTree(p->getLeft()); // evalute left child
    double rightValue = evaluateTree(p->getRight()); // evaluate right child
    char op = p->getElem()[0]; // get operation to perform
    switch (op) {
    case '+': return leftValue + rightValue;
    case '-': return leftValue - rightValue;
    case '*': return leftValue * rightValue;
    case '/': 
        if (rightValue == 0)
        {
            throw MathError(); // throw exception when dividing by 0
        }
        return leftValue / rightValue;
    default: return 0; // Invalid operator
    }
}

void TreeEvaluator::buildExpressionTree(std::string expression)
{
    destroy(); // destroy old tree

    if (isOperator(expression[0]) || isOperator(expression.back())) {
        throw SyntaxError(); // throw exception if there is an operator at the beginning or end of expression
    }

    std::istringstream iss(expression);
    ListStack<Position<std::string>*> nodes; // nodes stack used to build the nodes of the tree
    ListStack<char> operators; // stack of operators used to build nodes
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
                throw SyntaxError(); // throw exception if two consecutive operators
            }

            Position<std::string>* temp = new Position<std::string>;
            temp->elem = "";
            while (!numberStack->empty()) // empty the number stack
            {
                temp->elem = numberStack->top() + temp->elem; // add all chars of the number stack to the temp string
                numberStack->pop();
            }
            nodes.push(temp); // push the node holding the entire value into the stack

            if (!operators.empty()) // repeat until operators stack is empty
            {
                while (precedence(operators.top()) >= precedence(token)) // check precedence relation
                {
                    Position<std::string>* newNode2 = new Position<std::string>;
                    newNode2->setElem(std::string(1, operators.top())); // convert char to string
                    newNode2->right = nodes.top(); // provide the right child
                    nodes.pop(); // pop right child
                    newNode2->left = nodes.top(); // provide the left child
                    nodes.pop(); // pop left child
                    nodes.push(newNode2); // push the new node into the stack holding operation and both operands
                    operators.pop(); // pop operation
                    if (operators.empty())
                    {
                        break;
                    }
                }
            }
            operators.push(token); // add operation to operator stack
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
    while (!numberStack->empty()) // empty the number stack
    {
        temp->elem = numberStack->top() + temp->elem; // add all chars of the number stack to the temp string
        numberStack->pop();
    }
    nodes.push(temp); // push the node holding the entire value into the stack

    // Process remaining operators
    while (!operators.empty())
    {
        Position<std::string>* newNode = new Position<std::string>;
        newNode->setElem(std::string(1, operators.top())); // convert char to string
        newNode->right = nodes.top(); // provide the right child
        nodes.pop(); // pop right child
        newNode->left = nodes.top(); // provide the left child
        nodes.pop(); // pop left child
        nodes.push(newNode); // push the new node into the stack holding operation and both operands
        operators.pop(); // pop operation
    }
    expressionTree->root = nodes.top(); // set root of expression tree
}



bool TreeEvaluator::isOperator(char c) const
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

double TreeEvaluator::stringToDouble(const std::string str) const
{
    return std::stod(str);
}