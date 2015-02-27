// Extension of Array.h

/// Default constructor
template<typename T>
Array<T>::Array()
: count(0)
, capacity(0)
, _buffer(nullptr)
{

}

/// Construct the array with an initial size
template<typename T>
Array<T>::Array(std::size_t _size)
: count(_size)
, capacity(_size)
, _buffer(nullptr)
{
	reserve(_size);
}

/// Ensure the data buffer is deallocated
template<typename T>
Array<T>::~Array()
{
	if (capacity > 0)
	{
		if (!std::is_pod<T>())
		{
			// Isn't a POD, need to destruct
			for (std::size_t i = 0; i < capacity; ++i)
			{
				_buffer[i].~T();
			}

			free(_buffer);
		}
	}
}

/// Get the number of elements in the array
template<typename T>
inline std::size_t Array<T>::size()
{
	return count;
}

/// Push back a new element to the end of the container
template<typename T>
void Array<T>::push_back(const T& v)
{
	if (capacity == count)
	{
		reserve(capacity * 2 + 1);
	}

	_buffer[count++] = v;
}

/// Removes the last element in the container but does not reduce capacity size in memory
template<typename T>
void Array<T>::pop_back()
{
	if (count > 0)
		--count;
}

/// Reserve this amount of bytes as the full storage capacity of this array
/// This is the only place that allocates memory for the array
template<typename T>
void Array<T>::reserve(std::size_t bytes)
{
	_buffer = static_cast<T*>(realloc(_buffer, bytes * sizeof(T)));
	capacity = bytes;

	// Ensure the non-pod is constructed
	if (!std::is_pod<T>())
	{
		for (std::size_t i = 0; i < capacity; ++i)
		{
			new ((void*)_buffer[i]) T();
		}
	}
}

/// Set a new size for the array, expanding the max capacity if needed
template<typename T>
void Array<T>::resize(std::size_t _size)
{
	if (capacity < _size)
	{
		reserve(_size);
	}

	count = _size;
}

/// Get the iterator to the first element
template<typename T>
inline typename Array<T>::iterator Array<T>::begin() const
{
	return &_buffer[0];
}

/// Get the iterator to the last element
template<typename T>
inline typename Array<T>::iterator Array<T>::end() const
{
	return &_buffer[count];
}

/// Get a modifiable reference to the element at index
template<typename T>
T& Array<T>::operator[](std::size_t index)
{
	return _buffer[index];
}

/// Get a modifiable reference to the element at index
template<typename T>
const T& Array<T>::operator[](std::size_t index) const
{
	return _buffer[index];
}