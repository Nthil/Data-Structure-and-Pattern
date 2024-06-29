#pragma once
#include "BinaryTreeNode.h"
#include <stdexcept>
// Problem 3 requirement
template<typename T>
class BinarySearchTreeIterator;
template<typename T>
class BinarySearchTree
{
private:
	using BNode = BinaryTreeNode<T>;
	using BTreeNode = BNode*;
	BTreeNode fRoot;

public:
	BinarySearchTree() : fRoot((&BNode::NIL)) {}
	~BinarySearchTree()
	{
		while (!fRoot->empty())
		{
			delete fRoot;
		}
	}

	// Checks if the binary search tree is empty
	bool empty() const
	{
		return fRoot->empty();
	}

	// Returns the height of the binary search tree
	size_t height() const
	{
		while (empty())
		{
			throw domain_error("Empty tree has no height.");
		}
		return fRoot->height();
	}

	// Inserts a new key into the binary search tree
	bool insert(const T& aKey)
	{

		if (empty())
		{
			fRoot = new BNode(aKey);
			return true;
		}

		BTreeNode currentNode = fRoot;
		while (true)
		{

			if (aKey < currentNode->key)
			{

				if (currentNode->left == &BNode::NIL)
				{
					currentNode->left = new BNode(aKey);
					return true;
				}
				currentNode = currentNode->left;
			}

			else if (aKey > currentNode->key)
			{

				if (currentNode->right == &BNode::NIL)
				{
					currentNode->right = new BNode(aKey);
					return true;
				}
				currentNode = currentNode->right;
			}

			else
			{
				return false; // Key already exists in the tree
			}
		}
	}

	// Removes a key from the binary search tree
	bool remove(const T& aKey)
	{

		if (empty())
		{
			throw domain_error("Unable to remove from an empty tree.");
		}

		if (fRoot->leaf())
		{

			if (fRoot->key == aKey)
			{
				fRoot = &BNode::NIL;
				return true;
			}
			return false;
		}

		return fRoot->remove(aKey, &BNode::NIL);
	}

	// Problem 3 methods

	using Iterator = BinarySearchTreeIterator<T>;
	// Allow iterator to access private member variables
	friend class BinarySearchTreeIterator<T>;
	Iterator begin() const
	{
		return Iterator(*this).begin();
	}
	Iterator end() const
	{
		return Iterator(*this).end();
	}
};