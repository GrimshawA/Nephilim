#ifndef NephilimAllocator_h__
#define NephilimAllocator_h__

#include <Nephilim/Platform.h>

#include <stdint.h>

NEPHILIM_NS_BEGIN

/**
	\class Allocator
	\brief Preallocates memory for storing data later
*/
class NEPHILIM_API Allocator
{
public:

	/// Where the memory that belongs to this allocator begins
	void* _addr = nullptr;

	/// How big is the buffer this allocator has access to
	uint32_t size = 0;

public:

	/// Ensure the memory buffer is deleted, if we have pure ownership
	~Allocator();
};

/**
	\class HeapAllocator
	\brief Allows to allocate memory and free it on demand, like the native new and delete

	This is pretty much like the native heap, except it operates on a pre allocated block.
	It doesn't give any promises of cache locality, its just a way to use a big chunk allocated beforehand
	for unmanaged variables.
*/
class NEPHILIM_API HeapAllocator : public Allocator
{

};

NEPHILIM_NS_END
#endif // NephilimAllocator_h__
