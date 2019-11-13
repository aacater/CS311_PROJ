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

template<typename T>
class BinarySearchTree
{
private:
	struct BSTNode
	{
		T key;
		
		std::unique_ptr<BSTNode> _parent;
		std::unique_ptr<BSTNode> _leftChild;
		std::unique_ptr<BSTNode> _rightChild;
	};

private:
	std::unique_ptr<BSTNode> _root;

public:
	BinarySearchTree() {}
	~BinarySearchTree() = default;

	BinarySearchTree(const BinarySearchTree & other) = default;
	BinarySearchTree(BinarySearchTree && other) = default;
	BinarySearchTree& operator=(const BinarySearchTree & other) = default;
	BinarySearchTree& operator=(BinarySearchTree && other) = default;

	void inorder()
	{

	}

	void insert(T val)
	{
		if (_root == nullptr)
		{
			
		}
		
	}

};

// treesort
// Sort a given range using Treesort.
// Pre:
//     ???
// Requirements on Types:
//     ???
// Exception safety guarantee:
//     ???
template<typename FDIter>
void treesort(FDIter first, FDIter last)
{
    // ValType is the type that FDIter points to
    using ValType = typename std::iterator_traits<FDIter>::value_type;

    // THE FOLLOWING IS DUMMY CODE. IT WILL PASS ALL TESTS, BUT IT DOES
    // NOT MEET THE REQUIREMENTS OF THE PROJECT.
    std::vector<ValType> buff(std::distance(first, last));
    std::move(first, last, buff.begin());
    std::stable_sort(buff.begin(), buff.end());
    std::move(buff.begin(), buff.end(), first);
}

#endif //#ifndef FILE_TREESORT_H_INCLUDED

