#pragma once

#pragma once
template <typename E> class binaryTree;
class EvaluationController;

template <typename E> class Position {
public:
	Position() { parentNode = left = right = nullptr; } // constructor
	bool isRoot() { return parentNode == nullptr; } // returns 1 if the Position is a root node
	bool isExternal() { return ((left == nullptr) && (right == nullptr)); } // returns 1 if the Position is external
	int depth(); // returns the depth of the node
	Position<E>* getLeft() { return left; } // get left child
	Position<E>* getRight() { return right; } // get right child
	Position<E>* getParent() { return parentNode; } // get parent node
	E getElem() { return elem; } // get element held in position
	void setElem(E i) { elem = i; } // function to modify the element held in node
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