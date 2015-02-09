#ifndef NephilimFoundationArray_h__
#define NephilimFoundationArray_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class Array
	\brief Standard engine implementation for contiguous arrays
*/
template<typename T>
class NEPHILIM_API Array
{
private:

	/// Current total capacity of the array
	std::size_t capacity = 0;

	/// Current total count of elements in the array
	std::size_t count = 0;

	/// The contents buffer
	T* _buffer;

public:

	typedef const T* iterator;

	/// Default constructor
	Array();

	/// Construct the array with an initial size
	Array(std::size_t _size);

	/// Ensure the data buffer is deallocated
	~Array();

	/// Get the number of elements in the array
	std::size_t size();

	/// Reserve this amount of bytes as the full storage capacity of this array
	void reserve(std::size_t bytes);

	/// Set a new size for the array, expanding the max capacity if needed
	void resize(std::size_t _size);

	/// Push back a new element to the end of the container
	void push_back(const T& v);

	/// Removes the last element in the container but does not reduce capacity size in memory
	void pop_back();

	/// Access and modify the last element of the container
	T& last();

	/// Get the iterator to the first element
	iterator begin() const;

	/// Get the iterator to the last element
	iterator end() const;

	/// Get a modifiable reference to the element at index
	T& operator[](std::size_t index);

	/// Get a read-only reference to the element at index
	const T& operator[](std::size_t index) const;

};

#include <Nephilim/Foundation/Array.inl>

NEPHILIM_NS_END
#endif // NephilimAllocator_h__
