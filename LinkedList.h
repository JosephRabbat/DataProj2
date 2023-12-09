#pragma once
#include "ListNode.h"
#include "EmptyContainer.h"
#include <iostream>
// Linked List of type E
template <typename E> class LinkedList
{
private:
	ListNode<E>* head;
	ListNode<E>* tail;
	int csize;
public:
	LinkedList(); // constructor
	~LinkedList(); // destructor
	bool empty() const; // returns 1 if linked list is empty
	void addFront(const E e); // function to add at the head of the list
	void removeFront() throw(EmptyContainer); // function to remove from the front of the list
	void addBack(const E e); // function to add at the tail of the list
	void print() const; // function to print the list 
 	const E readFront() const throw(EmptyContainer); // function to read at the head
	const E readBack() const throw(EmptyContainer); // function to read at the tail
	const int size() const; // returns the number of nodes
};
template<typename E> inline LinkedList<E>::LinkedList()
{
	head = tail = nullptr;
	csize = 0;
}
template <typename E> LinkedList<E>::~LinkedList()
{
	while (!empty())
	{
		removeFront();
	}
}
template <typename E> bool LinkedList<E>::empty() const
{
	return csize == 0;
}
template <typename E> void LinkedList<E>::addFront(E e)
{
	ListNode<E>* temp = new ListNode<E>;
	temp->data = e;
	if (empty())
	{
		head = tail = temp;
	}
	else {
		temp->next = head;
		head = temp;
	}
	csize++;
}
template <typename E> void LinkedList<E>::removeFront()
{
	if (empty()) throw EmptyContainer("Empty List");
	ListNode<E>* temp = head;
	head = temp->next;
	delete temp;
	csize--;
}
template <typename E> void LinkedList<E>::addBack(E e)
{
	ListNode<E>* temp = new ListNode<E>;
	temp->data = e;
	if (empty())
	{
		head = tail = temp;
	}
	else {
		tail->next = temp;
		tail = temp;
	}
	csize++;
}
template <typename E> void LinkedList<E>::print() const
{
	int i = 0;
	ListNode<E>* temp = head;
	while (temp != nullptr)
	{
		std::cout << temp->data << std::endl;
		temp = temp->next;
	}
}
template<typename E>
inline const E LinkedList<E>::readFront() const
{
	if (empty()) throw EmptyContainer("Empty List");
	return head->NodeData();
}
template<typename E>
inline const E LinkedList<E>::readBack() const
{
	if (empty()) throw EmptyContainer("Empty List");
	return tail->NodeData();
}
template<typename E>
inline const int LinkedList<E>::size() const
{
	return csize;
}