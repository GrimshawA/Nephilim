#include <Nephilim/IndexArray.h>

NEPHILIM_NS_BEGIN

void IndexArray::redirectFromTo(Int32 searchElement, Int32 becomes)
{
	for(size_t i = 0; i < indices.size(); ++i)
	{
		if(indices[i] == searchElement)
		{
			indices[i] = becomes;
		}
	}
}

/// Whatever pointed at index1, now points at index 2, and vice versa
void IndexArray::swapIndices(Int32 index1, Int32 index2)
{
	for(size_t i = 0; i < indices.size(); ++i)
	{
		if(indices[i] == index1)
		{
			indices[i] = index2;
		}
		else if(indices[i] == index2)
		{
			indices[i] = index1;
		}
	}
}

size_t IndexArray::size()
{
	return indices.size();
}

NEPHILIM_NS_END