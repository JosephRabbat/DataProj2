#pragma once
#include <iostream>
#include "Position.h"

class EvaluationController;

template <typename E> class binaryTree
{
private:
	Position<E>* root; // root node of tree
	void inorder(Position<E>* p) const; // recursive inorder traversal
	void preorder(Position<E>* p) const; //  recursive preorder traversal
	void postorder(Position<E>* p) const; // recursive postorder traversal
	int height(Position<E>* p) const; // recursive height of tree
	int max(int x, int y) const; // max value between x and y
	int nodeCount(Position<E>* p) const; // recursive number of nodes in tree
	int leavesCount(Position<E>* p) const; // recursive number of leaves in tree
	void recursiveDestroy(Position<E>* p); // recursive function to destroy all the nodes
	void recursivePrint(Position<E>* p) const; // recursive function to print the tree
public:
	binaryTree() { root = nullptr; } // constructor
	~binaryTree() { destroy(); }; // destructor
	bool isEmpty() const { return root == nullptr; } // returns 1 if the tree is empty
	void inorderTraversal() const { inorder(root); };  // inorder traversal of tree
	void preorderTraversal() const { preorder(root); } // preorder traversal of tree
	void postorderTraversal() const { postorder(root); }; // postorder traversal of tree
	int treeHeight() const { return height(root); }; // returns the height of the tree
	int treeNodeCount() const { return nodeCount(root); }; // returns the number of nodes
	int treeLeavesCount() const { return leavesCount(root); }; // returns the number of leaves
	void destroy(); // destroys the tree
	Position<E>* getRoot() { return root; } // returns the root
	void print() const; // prints the tree
	friend class TreeEvaluator;
};

template<typename E> void binaryTree<E>::inorder(Position<E>* p) const
{
	if (p != nullptr) // perform inorder traversal from node p
	{
		inorder(p->getLeft());
		std::cout << p->getElem() << " ";
		inorder(p->getRight());
	}
}

template<typename E> void binaryTree<E>::preorder(Position<E>* p) const
{
	if (p != nullptr) // perform preorder traversal from node p
	{
		std::cout << p->getElem() << " ";
		preorder(p->getLeft());
		preorder(p->getRight());
	}
}

template<typename E> void binaryTree<E>::postorder(Position<E>* p) const
{
	if (p != nullptr) // perform postorder traversal from node p
	{
		postorder(p->getLeft());
		postorder(p->getRight());
		std::cout << p->getElem() << " ";
	}
}

template<typename E> int binaryTree<E>::height(Position<E>* p) const
{
	// return height from node p
	if (p == nullptr) return 0;
	return 1 + max(height(p->getLeft()), height(p->getRight()));
}

template<typename E> int binaryTree<E>::max(int x, int y) const
{
	if (x >= y) return x;
	return y;
}

template<typename E> int binaryTree<E>::nodeCount(Position<E>* p) const
{
	// return node count from node p
	return 1 + nodeCount(p->getLeft()) + nodeCount(p->getRight());
}

template<typename E> int binaryTree<E>::leavesCount(Position<E>* p) const
{
	// return leaves count from node p
	if (p->isExternal()) return 1;
	return leavesCount(p->getRight()) + leavesCount(p->getLeft());
}

template<typename E> void binaryTree<E>::recursiveDestroy(Position<E>* p)
{
	// recursively destroy node and children
	if (p != nullptr)
	{
		recursiveDestroy(p->getLeft());
		recursiveDestroy(p->getRight());
		delete p;
	}
}

template<typename E> void binaryTree<E>::destroy()
{
	recursiveDestroy(root); // destroy whole tree
}

template<typename E> void binaryTree<E>::print() const
{
	recursivePrint(root); // print whole tree
}

template<typename E> void binaryTree<E>::recursivePrint(Position<E>* pos) const
{
	// recursively print node and children
	for (int i = 0; i < pos->depth(); i++)
	{
		std::cout << " ";
	}
	std::cout << pos->elem << "\n";
	if (!pos->isExternal())
	{
		recursivePrint(pos->getLeft());
		recursivePrint(pos->getRight());
	}
}