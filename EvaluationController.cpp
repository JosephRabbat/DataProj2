#include "EvaluationController.h"

void EvaluationController::setExpression(std::string expr)
{
    expression = expr; // set expression
}

EvaluationController::EvaluationController()
{
    expression = ""; // initialize expression
}

EvaluationController::~EvaluationController() // destructor
{
    destroyExpressionTree();
    Stacks.~StackEvaluator();
}

double EvaluationController::evaluateUsingTree()
{
    Tree.buildExpressionTree(expression); return Tree.evaluateTree(Tree.getRoot());
    // build tree then evaluate it
}

void EvaluationController::destroyExpressionTree()
{
    Tree.destroy(); // destroy the tree
}

double EvaluationController::evaluateUsingStacks()
{
    return Stacks.evaluate(expression); // evaulate using stacks
}
