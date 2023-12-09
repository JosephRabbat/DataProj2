#pragma once
#include <stdexcept>
class SyntaxError : public std::runtime_error
{
public:
	SyntaxError() : std::runtime_error("Syntax Error, Cannot proceed") {}; // exception stack is empty
};
