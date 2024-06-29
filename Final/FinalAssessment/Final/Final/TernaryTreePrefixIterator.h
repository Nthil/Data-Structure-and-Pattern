
// COS30008, Final Exam, 2022

#pragma once

#include "TernaryTree.h"

#include <stack>

template<typename T>
class TernaryTreePrefixIterator
{
private:
    using TTree = TernaryTree<T>;
    using TTreeNode = TTree*;
    using TTreeStack = std::stack<const TTree*>;

    const TTree* fTTree;                // ternary tree
    TTreeStack fStack;                  // traversal stack

public:

    using Iterator = TernaryTreePrefixIterator<T>;

    Iterator operator++(int)
    {
        Iterator old = *this;

        ++(*this);

        return old;
    }

    bool operator!=(const Iterator& aOtherIter) const
    {
        return !(*this == aOtherIter);
    }

/////////////////////////////////////////////////////////////////////////
// Problem 4: TernaryTree Prefix Iterator

private:

    // push subtree of aNode [30]
    void push_subtrees(const TTree* aNode)
    {
        const TTree* subtrees[] = { &(*aNode).getRight(), &(*aNode).getMiddle(), &(*aNode).getLeft() };

        for (const TTree* subtree : subtrees)
        {
            if (!subtree->empty())
            {
                fStack.push(const_cast<TTreeNode>(subtree));
            }
        }
    }

    // for auxiliaries [4,10]
    void resetStackAndPushRoot()
    {
        fStack = TTreeStack();
        fStack.push(const_cast<TTreeNode>(fTTree));
    }

    void resetStack()
    {
        fStack = TTreeStack();
    }

public:

    // iterator constructor [12]
    TernaryTreePrefixIterator(const TTree* aTTree) : fTTree(aTTree), fStack()
    {
        while (!(*fTTree).empty())
        {
            fStack.push(const_cast<TTreeNode>(fTTree));
            break; // Exit the loop after pushing once
        }
    }

    // iterator dereference [8]
    const T& operator*() const
    {
        return **fStack.top();
    }

    // prefix increment [12]
    Iterator& operator++()
    {
        if (!fStack.empty())
        {
            TTreeNode lPopped = const_cast<TTreeNode>(fStack.top());
            fStack.pop();
            push_subtrees(lPopped);
        }
        return *this;
    }

    // iterator equivalence [12]
    bool operator==(const Iterator& aOtherIter) const
    {
        return fTTree == aOtherIter.fTTree && fStack.size() == aOtherIter.fStack.size();
    }

    // auxiliaries [4,10]
    Iterator begin() const
    {
        Iterator temp = *this;
        temp.resetStackAndPushRoot();
        return temp;
    }

    Iterator end() const
    {
        Iterator temp = *this;
        temp.resetStack();
        return temp;
    } 
};