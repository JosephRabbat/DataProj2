#pragma once
#include "LinkedList.h"
// Queue of type E
template <typename E>
class Queue
{
private:
	LinkedList<E>* q;
public:
	Queue();
	~Queue();

	int size() const;
	bool empty() const;
	const E front() const throw(EmptyContainer);
	void enqueue(const E e);
	const E dequeue() throw(EmptyContainer);
};
template<typename E>
inline Queue<E>::Queue()
{
	q = new LinkedList<E>;
}
template<typename E>
inline Queue<E>::~Queue()
{
	while (!empty())

	{

		dequeue();

	}
}
template<typename E>
inline int Queue<E>::size() const
{

	return q->size();
}
template<typename E>
inline bool Queue<E>::empty() const
{

	return q->empty();
}
template<typename E>
inline const E Queue<E>::front() const
{

	if (empty()) throw(EmptyContainer("Empty Queue"));

	return q->readFront();
}
template<typename E>
inline void Queue<E>::enqueue(const E e)
{
	q->addBack(e);
}
template<typename E>
inline const E Queue<E>::dequeue()
{

	if (empty()) throw(EmptyContainer("Empty Queue"));
	E temp = q->readFront();
	q->removeFront();

	return temp;
}
