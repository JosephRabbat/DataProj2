#pragma once
#include <stdexcept>
class EmptyContainer : public std::runtime_error
{
public:
	EmptyContainer(std::string s) : std::runtime_error(s) {}
};