#pragma once
// Node of Linked List of type E
template <typename E> class LinkedList;
template <typename E> class ListNode
{
private:
	E data;
	ListNode<E>* next;
public:
	ListNode();
	E NodeData() const;
	friend class LinkedList<E>;
};
template<typename E>
inline ListNode<E>::ListNode()
{
	next = nullptr;
}
template<typename E>
E ListNode<E>::NodeData() const
{
	return data;
}