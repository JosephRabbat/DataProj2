#pragma once
#include "LinkedList.h"
#include "EmptyStack.h"
template<typename Element>
class ListStack
{
private:
	LinkedList<Element>* S;
public:
	ListStack() { S = new LinkedList<Element>; }; // Constructor
	~ListStack() { while (!empty()) pop(); }; // Destructor
	void pop() // pop element from stack
	{
		if (empty()) throw EmptyStack(); // exception if stack is empty
		S->removeFront();
	}
	void push(Element e) // push element into the stack
	{
		S->addFront(e);
	}
	Element top() // read element on top of the stack
	{
		if (empty()) throw EmptyStack(); // exception if stack is empty
		return S->readFront();
	}
	bool empty() // bool, 1 if stack is empty
	{
		return S->empty();
	}
};
