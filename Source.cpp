#include "EvaluationController.h"
#include "Queue.h"
#include <iostream>
#include <fstream>

void main() {
	EvaluationController evaluator;
	Queue<double> resultQueue;

	std::ifstream infile;
	infile.open("expressions.txt");
	std::string expression;

	while (infile >> expression)
	{
		evaluator.setExpression(expression);
		std::cout << "Expression: " << expression << "\n\n";
		try
		{
			std::cout << "Using Tree: " << evaluator.evaluateUsingTree() << "\n\n";
			std::cout << "Using Stacks: " << evaluator.evaluateUsingStacks() << "\n\n";
		}
		catch (std::exception e)
		{
			std::cerr << e.what() << "\n";
		}
		std::cout << "\n\n";
	}
}