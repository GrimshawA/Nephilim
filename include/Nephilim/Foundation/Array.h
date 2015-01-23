#ifndef NephilimFoundationArray_h__
#define NephilimFoundationArray_h__

#include <Nephilim/Platform.h>

#include <stdint.h>

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
	uint32_t capacity = 0;

	/// Current total count of elements in the array
	uint32_t count = 0;

	/// The contents buffer
	T* memory = nullptr;

public:

	/// Get the number of elements in the array
	int32_t size();
};

#include <Nephilim/Foundation/Array.inl>

NEPHILIM_NS_END
#endif // NephilimAllocator_h__
