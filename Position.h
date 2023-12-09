#pragma once

#pragma once
template <typename E> class binaryTree;
class EvaluationController;

template <typename E> class Position {
public:
	Position() { parentNode = left = right = nullptr; }
	E& operator*() { return elem; }
	bool isRoot() { return parentNode == nullptr; }
	bool isExternal() { return ((left == nullptr) && (right == nullptr)); }
	int depth();
	Position<E>* getLeft() { return left; }
	Position<E>* getRight() { return right; }
	Position<E>* getParent() { return parentNode; }
	E getElem() { return elem; }
	void setElem(E i) { elem = i; }
	friend class TreeEvaluator;
	friend class binaryTree<E>;
private:
	E elem;
	Position<E>* parentNode;
	Position<E>* left;
	Position<E>* right;
};
template <typename E> int Position<E>::depth()
{
	if (isRoot())
		return 0;
	else
		return 1 + getParent()->depth();
}