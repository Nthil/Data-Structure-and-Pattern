
// COS30008, Problem Set 4, Problem 3, 2022

#pragma once

#include "BinarySearchTree.h"

#include <stack>

template<typename T>
class BinarySearchTreeIterator
{
private:

	using BSTree = BinarySearchTree<T>;
	using BNode = BinaryTreeNode<T>;
	using BTreeNode = BNode*;
	using BTNStack = std::stack<BTreeNode>;
	const BSTree& fBSTree; // binary search tree
	BTNStack fStack; // DFS traversal stack

	void pushLeft(BTreeNode aNode)
	{
		while (!aNode->empty())
		{
			fStack.push(aNode);
			aNode = aNode->left;
		}
	}

public:

	using Iterator = BinarySearchTreeIterator<T>;

	BinarySearchTreeIterator(const BSTree& aBSTree) : fBSTree(aBSTree), fStack()
	{
		pushLeft(aBSTree.fRoot);
	}

	// Dereference operator to get the value at the current position
	const T& operator*() const
	{
		return fStack.top()->key;
	}

	// Pre-increment operator (++iter)
	Iterator& operator++()
	{
		BTreeNode lPop = fStack.top();
		fStack.pop();
		pushLeft(lPop->right);
		return *this;
	}

	// Post-increment operator (iter++)
	Iterator operator++(int)
	{
		// Create a temporary iterator and move it to the end of the tree
		Iterator temp = *this;

		while (!temp.fStack.empty())
		{
			BTreeNode currentNode = temp.fStack.top();
			temp.fStack.pop();

			BTreeNode rightNode = currentNode->right;
			while (rightNode->nonEmpty())
			{
				temp.fStack.push(rightNode);
				rightNode = rightNode->left;
			}
		}

		return temp;
	}

	// Check if two iterators are equal or not
	bool isEqual(const Iterator& aOtherIter) const
	{
		return &fBSTree == &aOtherIter.fBSTree && fStack == aOtherIter.fStack;
	}
	bool operator!=(const Iterator& aOtherIter) const
	{
		return !isEqual(aOtherIter);
	}

	// Return an iterator pointing to the beginning of the tree
	Iterator begin() const
	{
		Iterator temp = *this;
		temp.fStack = BTNStack();
		temp.pushLeft(temp.fBSTree.fRoot);
		return temp;
	}

	// Return an iterator pointing to the end of the tree
	Iterator end() const
	{
		Iterator temp = *this;
		temp.fStack = BTNStack();
		return temp;
	}
};