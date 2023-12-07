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
	LinkedList();
	~LinkedList();
	bool empty() const;
	void addFront(const E e);
	void removeFront() throw(EmptyContainer);
	void addBack(const E e);
	void print() const;
	const E readFront() const throw(EmptyContainer);
	const E readBack() const throw(EmptyContainer);
	const int size() const;
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