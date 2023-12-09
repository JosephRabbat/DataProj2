#pragma once
#include <iostream>
#include "Position.h"

class EvaluationController;

template <typename E> class binaryTree
{
private:
	Position<E>* root;
	void inorder(Position<E>* p) const;
	void preorder(Position<E>* p) const;
	void postorder(Position<E>* p) const;
	int height(Position<E>* p) const;
	int max(int x, int y) const;
	int nodeCount(Position<E>* p) const;
	int leavesCount(Position<E>* p) const;
	void recursiveDestroy(Position<E>* p);
	void recursivePrint(Position<E>* p) const;
public:
	binaryTree() { root = nullptr; }
	~binaryTree() { destroy(); };
	bool isEmpty() const { return root == nullptr; }
	void inorderTraversal() const { inorder(root); };
	void preorderTraversal() const { preorder(root); }
	void postorderTraversal() const { postorder(root); };
	int treeHeight() const { return height(root); };
	int treeNodeCount() const { return nodeCount(root); };
	int treeLeavesCount() const { return leavesCount(root); };
	void destroy();
	Position<E>* getRoot() { return root; }
	void print() const;
	friend class TreeEvaluator;
};

template<typename E> void binaryTree<E>::inorder(Position<E>* p) const
{
	if (p != nullptr)
	{
		inorder(p->getLeft());
		std::cout << p->getElem() << " ";
		inorder(p->getRight());
	}
}

template<typename E> void binaryTree<E>::preorder(Position<E>* p) const
{
	if (p != nullptr)
	{
		std::cout << p->getElem() << " ";
		preorder(p->getLeft());
		preorder(p->getRight());
	}
}

template<typename E> void binaryTree<E>::postorder(Position<E>* p) const
{
	if (p != nullptr)
	{
		postorder(p->getLeft());
		postorder(p->getRight());
		std::cout << p->getElem() << " ";
	}
}

template<typename E> int binaryTree<E>::height(Position<E>* p) const
{
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
	return 1 + nodeCount(p->getLeft()) + nodeCount(p->getRight());
}

template<typename E> int binaryTree<E>::leavesCount(Position<E>* p) const
{
	if (p->isExternal()) return 1;
	return leavesCount(p->getRight()) + leavesCount(p->getLeft());
}

template<typename E> void binaryTree<E>::recursiveDestroy(Position<E>* p)
{
	if (p != nullptr)
	{
		recursiveDestroy(p->getLeft());
		recursiveDestroy(p->getRight());
		delete p;
	}
}

template<typename E> void binaryTree<E>::destroy()
{
	recursiveDestroy(root);
}

template<typename E> void binaryTree<E>::print() const
{
	recursivePrint(root);
}

template<typename E> void binaryTree<E>::recursivePrint(Position<E>* pos) const
{
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