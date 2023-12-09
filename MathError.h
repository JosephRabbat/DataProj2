#pragma once
#include <stdexcept>
class MathError : public std::runtime_error
{
public:
	MathError() : std::runtime_error("Math Error, Cannot continue with the calculation") {};
};

