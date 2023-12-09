#include "EvaluationController.h"
#include "Queue.h"
#include <iostream>
#include <fstream>

void main() {
	EvaluationController evaluator; // create the evaluation controller
	Queue<std::string> resultQueue; // create the result queue

	std::ifstream infile;
	infile.open("expressions.txt");
	std::string expression;

	while (infile >> expression) // read expression from file
	{
		resultQueue.enqueue(expression); // add expression into the result queue
		evaluator.setExpression(expression); // prepare to compute the expression
		try
		{
			double result1 = evaluator.evaluateUsingTree(); // get the result of the expression using the evaluation tree
			std::string str1 = std::to_string(result1);
			str1.erase(str1.find_last_not_of('0') + 1, std::string::npos);
			str1.erase(str1.find_last_not_of('.') + 1, std::string::npos); // remove trailing zeros

			double result2 = evaluator.evaluateUsingStacks(); // get the result of the expression using stacks
			std::string str2 = std::to_string(result2);
			str2.erase(str2.find_last_not_of('0') + 1, std::string::npos);
			str2.erase(str2.find_last_not_of('.') + 1, std::string::npos); // remove trailing zeros

			resultQueue.enqueue("Using Tree: " + str1 + "\nUsing Stacks: " + str2); // add into the result queue
		}
		catch (std::exception e)
		{
			resultQueue.enqueue(e.what()); // if we catch an exception add it into the result queue
		}
	}

	int i = 1;

	while (!resultQueue.empty()) // empty the result queue and print everything
	{
		std::cout << "Expression " << i << ":\n" << resultQueue.dequeue() << "\n";
		std::cout<< resultQueue.dequeue() << "\n\n";
		i++;
	}


}