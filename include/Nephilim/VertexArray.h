#ifndef NephilimVertexArray_h__
#define NephilimVertexArray_h__

#include "Platform.h"

#include <vector>
#include <cstddef>

NEPHILIM_NS_BEGIN

class IndexArray;

/**
	\class Format
	\brief Vertex format specification
*/
class NEPHILIM_API VertexFormat
{
public:

	///< Hints about what an attribute is
	enum AttributeHint
	{
		Position,
		Color,
		TexCoord
	};

	/// \class Attribute
	/// \brief One of the vertex components
	class NEPHILIM_API Attribute
	{
	public:
		Attribute();
		Attribute(Int32 attributeByteSize, Int32 attributeNumComponents, AttributeHint attributeHint);

		Int32         size;            ///< Size, in bytes, of the data type
		Int32         numComponents;   ///< Number of components that make up this attribute's data
		AttributeHint hint;            ///< Hint about what this attribute actually is
	};

	bool                   segmented;  ///< Is each vertex contiguous or segmented in multiple arrays?
	std::vector<Attribute> attributes; ///< List of attributes that define the vertex format
};

/**
	\class VertexData
	\brief This structure holds vertex data

	1. This class is only a container for vertex data.
	2. It contains N vertices at once.
	3. All vertices have the same format.
	4. The format is dynamic and user specified
	5. Data for each vertex can be contiguous or segmented within the container
*/
class NEPHILIM_API VertexArray
{
public:
	void removeLast();

	Int32 getVertexSize();

	void swapVertices(Int32 index, Int32 goesTo);

	Int32 getAttributeOffset(Int32 attributeIndex);
	Int32 getAttributeSize(Int32 attributeIndex);

	bool isVertexEqual(Int32 index1, Int32 index2);

	void setVertexAttribute(Int32 vertexIndex, Int32 attributeIndex, void* data);

	void allocateData(Int32 vertexCount);

	static void removeDuplicateVertices(VertexArray& varray, IndexArray& iarray);

	VertexFormat       format; ///< Format of the vertex data
	std::vector<char>  data;   ///< The vertex raw data
	size_t             count;  ///< Number of allocated vertices
};

/**
	\class IndexData
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

	std::vector<Uint16> indices;
};


NEPHILIM_NS_END
#endif // NephilimVertexArray_h__
