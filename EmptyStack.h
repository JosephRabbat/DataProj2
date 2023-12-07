#pragma once
#include <stdexcept>
class EmptyStack : public std::runtime_error
{
public:
	EmptyStack() : std::runtime_error("Error, the stack is empty") {}; // exception stack is empty
};