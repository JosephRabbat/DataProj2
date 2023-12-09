#include "EvaluationController.h"

void EvaluationController::setExpression(std::string expr)
{
    expression = expr;
}

EvaluationController::EvaluationController()
{
    expression = "";
}

EvaluationController::~EvaluationController()
{
    destroyExpressionTree();
    Stacks.~StackEvaluator();
}

double EvaluationController::evaluateUsingTree()
{
    Tree.buildExpressionTree(expression); return Tree.evaluateTree(Tree.getRoot());
}

void EvaluationController::destroyExpressionTree()
{
    Tree.destroy();
}

void EvaluationController::printExpressionTree()
{
    Tree.print();
}

double EvaluationController::evaluateUsingStacks()
{
    return Stacks.evaluate(expression);
}
