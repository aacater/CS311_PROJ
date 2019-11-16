// treesort.h
// Alex Cater, Kurt Nunn, Christopher Seamount
// 2019-11-10
//
// For CS 311 Fall 2019
// Header for function template treesort
// There is no associated source file.

#ifndef FILE_TREESORT_H_INCLUDED
#define FILE_TREESORT_H_INCLUDED

#include <iterator>
// For std::iterator_traits
#include <algorithm>
// For std::stable_sort, std::move
#include <vector>
// For std::vector
#include <iterator>
// For std::distance
#include <memory>

#include<iostream>

template<typename ValType>
struct BSTNode
{
	ValType _key;

	std::unique_ptr<BSTNode> _left;
	std::unique_ptr<BSTNode> _right;

	BSTNode(ValType key) : _left(nullptr), _right(nullptr), _key(key) {}
};

// treesort
// Sort a given range using Treesort.
// Pre:
//     ???
// Requirements on Types:
//     ???
// Exception safety guarantee:
//     ???
// exception nuetral
template<typename FDIter>
void treesort(FDIter first, FDIter last)
{
    // ValType is the type that FDIter points to
    using ValType = typename std::iterator_traits<FDIter>::value_type;

	std::unique_ptr<BSTNode<ValType>> head = nullptr;

	for(FDIter it = first; it != last; ++it)
	{
		insert(head, *it);
	}

	inorder(head, first);
}
template<typename ValType, typename FDIter>
void inorder(std::unique_ptr<BSTNode<ValType>>& node, FDIter &loc)
{
	if (node != nullptr)
	{
		inorder(node->_left, loc);
		*loc++ = node->_key;
		inorder(node->_right, loc);
	}
	
}

template<typename ValType>
void insert(std::unique_ptr<BSTNode<ValType>>& node, const ValType& key)
{
	if (!node)
	{
		node = std::make_unique<BSTNode<ValType>>(key);
	}
	else if(key < node->_key)
	{
		insert(node->_left, key);
	}
	else
	{
		insert(node->_right, key);
	}
}

#endif //#ifndef FILE_TREESORT_H_INCLUDED