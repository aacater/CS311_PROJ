// tssarray.h
// Alex Cater, Chris Seamount, Kurt Nunn
// 2019-10-31
//
// For CS 311 Fall 2019
// Header for class TSSArray
// Some functions provided by Dr. Chappell in SSArray Class


#ifndef FILE_TSSARRAY_H_INCLUDED
#define FILE_TSSARRAY_H_INCLUDED
#include <cstddef>		// For std::size_t
#include <algorithm>	// For std::max

// *********************************************************************
// class TSSArray - Class definition
// *********************************************************************
// class TSSArray
// Templated Seriously Smart Array
// Resizable, copyable/movable, exception-safe.
// Invariants:
//     0 <= _size <= _capacity.
//     _data points to an array of int, allocated with new[], owned by
//      *this, holding _size templated type -- UNLESS _capacity == 0, which case
//      _data may be nullptr.
// Requirements on types:
//		dctor, move ctor, and move assignment must not throw
template <typename T>
class TSSArray {


	// ***** TSSArray: types *****
public:
	// value_type: type of data items
	using value_type = T;

	// size_type: type of sizes & indices
	using size_type = std::size_t;

	// iterator, const_iterator: random-access iterator types
	using iterator = value_type*;
	using const_iterator = const value_type*;


	// ***** TSSArray: internal-use constants *****
private:
	// Capacity of default-constructed object
	enum { DEFAULT_CAP = 16 };


	// ***** TSSArray: ctors, op=, dctor
public:
	// Default ctor & ctor from size
	// Pre:
	//	size >= 0
	// Strong Guarantee
	// Exception neutral
	explicit TSSArray(size_type size = 0)
		:_capacity(std::max(size, size_type(DEFAULT_CAP))),
		// _capacity must be declared before _data
		_size(size),
		_data(new value_type[_capacity])
	{}

	// Copy ctor
	// Pre:
	//	none.
	// Strong Guarantee
	// Exception neutral
	TSSArray(const TSSArray& other)
		:_capacity(other._capacity),
		_size(other._size),
		_data(new value_type[other._capacity])
	{
		try
		{
			std::copy(other.begin(), other.end(), begin());
		}
		catch (...)
		{
			delete[] _data;
			throw;
		}
	}

	// Move ctor
	// Pre:
	//	none.
	// No-Throw Guarantee
	// Exception neutral
	TSSArray(TSSArray&& other) noexcept
		:_capacity(other._capacity),
		_size(other._size),
		_data(other._data)
	{
		other._capacity = 0;
		other._size = 0;
		other._data = nullptr;
	}

	// Dctor
	// No-Throw Guarantee
	// Exception neutral
	~TSSArray()
	{
		delete[] _data;
	}

	// Copy assignment
	// Pre:
	//	none.
	// Strong Guarantee
	// Exception neutral
	TSSArray& operator=(const TSSArray& other)
	{
		TSSArray copy_of_other(other);
		swap(copy_of_other);
		return *this;
	}

	// Move assignment
	// Pre:
	//	none.
	// No-Throw Guarantee
	// Exception neutral
	TSSArray& operator=(TSSArray&& other) noexcept
	{
		swap(other);
		return *this;
	}


	// ***** TSSArray: general public operators *****
public:
	// Operator[] - non-const & const
	// Pre:
	//	index must be non-negative and within the array bounds.
	// No-Throw Guarantee
	value_type& operator[](size_type index) noexcept
	{
		return _data[index];
	}
	const value_type& operator[](size_type index) const noexcept
	{
		return _data[index];
	}


	// ***** TSSArray: general public functions *****
public:
	// size
	// Pre:
	//	none.
	// No-Throw Guarantee
	// Exception neutral
	size_type size() const noexcept
	{
		return _size;
	}

	// empty
	// Pre:
	//	none.
	// No-Throw Guarantee
	// Exception neutral
	bool empty() const noexcept
	{
		return size() == 0;
	}

	// begin - non-const & const
	// Pre:
	//	none.
	// No-Throw Guarantee
	// Exception neutral
	iterator begin() noexcept
	{
		return _data;
	}
	const_iterator begin() const noexcept
	{
		return _data;
	}

	// end - non-const & const
	// Pre:
	//	none.
	// No-Throw Guarantee
	// Exception neutral
	iterator end() noexcept
	{
		return begin() + size();
	}
	const_iterator end() const noexcept
	{
		return begin() + size();
	}

	// resize
	// Pre:
	//	newsize must be non-negative.
	// Strong Guarantee
	// Exception neutral
	void resize(size_type newsize)
	{
		// if new size > current size, must do reallocate-and-copy
		if(_capacity < newsize)
		{
			size_type newCap = std::max(std::max(newsize,_capacity*2), size_type(DEFAULT_CAP));
			value_type* new_arr;
			new_arr = new value_type[newCap];	
			try
			{
				std::copy(begin(), end(), new_arr);
			}
			catch (...)
			{
				delete[] new_arr;
				throw;
			}
			std::swap(_data, new_arr);
			std::swap(_capacity, newCap);
			std::swap(_size, newsize);
			delete[] new_arr;
		}
		else
		{
			_size = newsize;
		}
	}

	// insert
	// Pre:
	//	pos is a valid iterator position inside the array (begin() <= pos <= end())
	// Basic Guarantee
	// Exception neutral
	iterator insert(iterator pos,
		const value_type& item)
	{
		auto itr = pos - begin();
		resize(size() + 1);
		_data[size() - 1] = item;
		std::rotate(begin() + itr, end()-1, end()); // moves pos element to end
		return begin() + itr;
	}


	// erase
	// Pre:
	//	pos is a valid iterator position inside the array (begin() <= pos <= end())
	// Basic Guarantee
	// Exception neutral
	iterator erase(iterator pos)
	{
		auto itr = pos - begin();
		std::rotate(begin() + itr, begin() + itr + 1, end()); // moves pos element to end
		resize(size() - 1);
		return begin() + itr;
	}

	// push_back
	// Pre:
	//	none.
	// InsertEnd operation.
	// Basic Guarantee
	// Exception neutral
	void push_back(const value_type& item)
	{
		insert(end(), item);
	}
	// pop_back
	// Pre:
	//     _size > 0.
	// Strong Guarantee
	// Exception neutral
	void pop_back()
	{
		erase(end() - 1);
	}

	// swap
	// Pre:
	// 	none.
	// No-Throw Guarantee
	// Exception neutral
	void swap(TSSArray& other) noexcept
	{
		std::swap(_capacity, other._capacity);
		std::swap(_size, other._size);
		std::swap(_data, other._data);
	}


	// ***** TSSArray: data members *****
private:
	size_type	_capacity;  // Size of our allocated array
	size_type	_size;      // Size of client's data
	value_type*	_data;      // Pointer to our array

};  // End class TSSArray

#endif //#ifndef FILE_TSSARRAY_H_INCLUDED
