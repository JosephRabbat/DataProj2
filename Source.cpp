#include "ExpressionEvaluator.h"
#include <iostream>

void main() {
	ExpressionEvaluator evaluator;
	std::string expression = "4+6*17.2-2";
	evaluator.setExpression(expression);
	std::cout << "Expression: " << expression << "\n\n";
	std::cout << "Using Stacks: " << evaluator.evaluateUsingStacks() << "\n\n";
	std::cout << "Using Tree: " << evaluator.evaluateUsingTree() << "\n\n";
}