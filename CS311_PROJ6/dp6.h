// dp6.h
// Alex Cater
// 2019-11-07
//
// For CS 311 Fall 2019
// Header for Project 6 code


#ifndef FILE_DP6_H_INCLUDED
#define FILE_DP6_H_INCLUDED

#include <cstddef> // For std::size_t
#include <memory> // For std::unique, std::make_unique
#include <utility> // For std::pair, std::make_pair
#include "llnode2.h"

// reverseList
// Reverse a linked list; in-place, linear time, and performs no value type
// operations.
// Exception neutral
template<typename ValType>
void reverseList(unique_ptr<LLNode2<ValType>>& head)
{
	// TODO
}


// ============================================================================
// class template LLMap
// ============================================================================

// class template LLMap
// Template for an associative linked list.
//
// Requirements on Types:
// - KType and VType meet the type requirements of std::pair and std::make_pair
//   from <utility>.
// - KType has a public operator== that offers at least the Strong Guarantee.
// - KType has a copy ctor that offers at least the Strong Guarentee.
// - VType has a copy ctor and a copy assignment operator that offer at least
//   the Strong Guarantee.
// - KType and VType have non-throwing dctors.
//
// Invariants:
// - _head is empty or points to an empty-ptr-terminated singly linked list.
// - Each node in the list stores a key-value pair whose key type is key_type
//   and whose value type is value_type.
// - Each key in the list appears only once.
// - 0 <= number of nodes <= maximum value for type size_type.
template <typename KType, typename VType>
class LLMap {

	// LLMap: Public member types
public:
	using key_type = KType;	// Type of keys.
	using value_type = VType;	// Type of associated values.
	using kvpair_type = std::pair<key_type, value_type>;	// Type of key-value pairs.
	using node_type = LLNode2<kvpair_type>;	// Type of list nodes.
	using size_type = std::size_t;	// Type of list size.

	// LLMap: Default ctor and the Big Five
public:

	// Default ctor
	// Create an empty list.
	//
	// No-Throw Guarantee
	// Exception neutral
	LLMap() noexcept
		:_head()
	{
		// empty
	}

	// Dctor
	//
	// No-Throw Guarantee
	// Exception neutral
	~LLMap() = default;

	// Copy ctor, move ctor, copy assignment operator, move assignment operator
	LLMap(const LLMap& other) = delete;
	LLMap(LLMap&& other) = delete;
	LLMap& operator=(const LLMap& other) = delete;
	LLMap& operator=(LLMap&& other) = delete;

	// LLMap: General public member functions
public:

	// size
	// Return the number of nodes in the list.
	//
	// Strong Guarantee
	// Exception neutral
	// based on llnode2.h's size function
	size_type size() const
	{
		auto p = _head.get();  // Iterates through list
		size_t counter = 0;   // Number of nodes so far
		while (p != nullptr)
		{
			++counter;
			p = p->_next.get();
		}
		return counter;
	}

	// empty
	// Return whether the list is empty.
	//
	// No-Throw Guarantee
	// Exception neutral
	bool empty() const
	{
		return !(_head);
	}

	// find - non-const & const
	// If the list contains the given key, return a pointer to the associated
	// value. Otherwise return nullptr.
	//
	// Strong Guarantee
	// Exception neutral
	value_type* find(key_type key)
	{
		auto node = lookup(key);
		if (node)
		{
			return &(node->_data.second);
		}
		return nullptr;
	}
	const value_type* find(key_type key) const
	{
		auto node = lookup(key);
		if (node)
		{
			return &(node->_data.second);
		}
		return nullptr;
	}

	// insert
	// Add a key-value pair to the list. If the list already contains the given
	// key, overwrite its associated value with the given value.
	//
	// Strong Guarantee
	// Exception neutral
	void insert(key_type key, value_type value)
	{
		value_type* val_loc = find(key);

		if (val_loc) {
			*val_loc = value;
		}
		else {
			//_head = move(make_unique<node_type>(std::make_pair(key, value), _head));
			
		}
	}

	// erase
	// If the list contains the given key, remove that key-value pair.
	// Otherwise do nothing.
	//
	// Strong Guarantee
	// Exception neutral
	void erase(key_type key)
	{
		// TODO
	}

	// traverse
	// Call the given function on each key-value pair in the list.
	//
	// Requirements on Types:
	// - Func takes two parameters, the first of type key_type and the second
	//   of type value_type, and returns nothing.
	// - Func is either a function pointer or an object for which operator() is
	//   defined.
	// - Func offers the Strong Guarantee.
	//
	// Strong Guarantee
	// Exception neutral
	template <typename Func>
	void traverse(Func f)
	{
		// TODO
	}

	// ListMap: Private member functions
private:

	// lookup
	// If the list contains the given key, return a pointer to the node that
	// contains the key-value pair. Otherwise return an empty pointer.
	//
	// Strong Guarantee
	// Exception neutral, does not throw additional exceptions.
	node_type* lookup(key_type key) const {
		auto current = _head.get();
		while (current) {
			if (current->_data.first == key)
				return current;
			current = current->_next.get();
		}
		return current;
	}
	// LLMap: Private data members
private:
	std::unique_ptr<node_type> _head;

};  // End class template LLMap

#endif //#ifndef FILE_DP6_H_INCLUDED