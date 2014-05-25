#ifndef NephilimIndexArray_h__
#define NephilimIndexArray_h__

#include <Nephilim/Platform.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class IndexArray
	\brief Geometric faces information

	Meant to be used together with VertexData,
	to make up the faces of the polygons with
	indices, using the vertex data.
*/
class NEPHILIM_API IndexArray
{
public:

	void redirectFromTo(Int32 searchElement, Int32 becomes);
	/// Whatever pointed at index1, now points at index 2, and vice versa
	void swapIndices(Int32 index1, Int32 index2);

	size_t size();

	std::vector<Uint16> indices;
};

NEPHILIM_NS_END
#endif // NephilimIndexArray_h__
