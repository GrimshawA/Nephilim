#include <Nephilim/VertexArray.h>
#include <Nephilim/IndexArray.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

VertexFormat::Attribute::Attribute()
{
}

VertexFormat::Attribute::Attribute(Int32 attributeByteSize, Int32 attributeNumComponents, AttributeHint attributeHint)
: size(attributeByteSize)
, numComponents(attributeNumComponents)
, hint(attributeHint)
{
}

//////////////////////////////////////////////////////////////////////////

void VertexArray::setVertexAttribute(Int32 vertexIndex, Int32 attributeIndex, void* data)
{
	char* dataAddress = reinterpret_cast<char*>(data);

	char* addressOfTarget = &dataAddress[0] + (getVertexSize() * vertexIndex) + getAttributeOffset(attributeIndex);

	memcpy(addressOfTarget, data, format.attributes[attributeIndex].size * format.attributes[attributeIndex].numComponents);
}

Int32 VertexArray::getAttributeOffset(Int32 attributeIndex)
{
	Int32 localOffset = 0;
	for(size_t i = 0; i < format.attributes.size(); ++i)
	{
		if(i == attributeIndex)
		{
			return localOffset;
		}

		localOffset += getAttributeSize(i);
	}
	return localOffset;
}

Int32 VertexArray::getAttributeSize(Int32 attributeIndex)
{
	return format.attributes[attributeIndex].size * format.attributes[attributeIndex].numComponents;
}

Int32 VertexArray::getVertexSize() const
{
	Int32 bytesPerVertex = 0;
	for(size_t i = 0; i < format.attributes.size(); ++i)
	{
		bytesPerVertex += format.attributes[i].numComponents * format.attributes[i].size;
	}
	return bytesPerVertex;
}

void VertexArray::allocateData(Int32 vertexCount)
{
	Int32 bytesPerVertex = getVertexSize();

	data.resize(bytesPerVertex * vertexCount);

	count = vertexCount;
}

bool VertexArray::isVertexEqual(Int32 index1, Int32 index2)
{
	char* v1 = &data[0] + getVertexSize() * index1;
	char* v2 = &data[0] + getVertexSize() * index2;

	if(memcmp(v1,v2, getVertexSize()) == 0)
	{
		return true;
	}
	else
		return false;
}

/// Get the pointer to the attribute data of a given vertex
char* VertexArray::getAttribute(Int32 attributeIndex, Int32 vertexIndex)
{
	return &data[0] + (getVertexSize() * vertexIndex) + getAttributeOffset(attributeIndex);
}

void VertexArray::removeLast()
{
	data.resize(data.size() - getVertexSize());
	count--;
}

/// Get the byte size of the current buffer
Int32 VertexArray::getMemorySize() const
{
	return data.size();
}

void VertexArray::swapVertices(Int32 index, Int32 goesTo)
{
	char* tbuffer = new char[getVertexSize()];

	// get the temp buffer from the index vertex
	memcpy(tbuffer, &data[0] + getVertexSize() * index, getVertexSize());

	// copy goesTo to the index vertex
	memcpy(&data[0] + getVertexSize() * index, &data[0] + getVertexSize() * goesTo, getVertexSize());
	
	// copy temp buffer to goesTo now
	memcpy(&data[0] + getVertexSize() * goesTo, tbuffer, getVertexSize());

	delete[] tbuffer;
}


void VertexArray::removeDuplicateVertices(VertexArray& varray, IndexArray& iarray)
{
	Log("Starting vertex count: %d", varray.count);
	
	// Lets remove duplicate vertices to get a smaller varray, iarray stays the same.

	// For each vertex, find duplicates after it
	for(size_t i = 0; i < varray.count ; ++i)
	{
		// For each i, iterate from i+1 to end
		for(size_t j = i + 1; j < varray.count; ++j)
		{
			if(varray.isVertexEqual(i,j))
			{
				
				// swap two vertices, also swap their references
				varray.swapVertices(j, varray.count-1);
				iarray.swapIndices(j, varray.count-1);
				
				varray.removeLast();

				// whatever indices were pointing at j, which is now gone, now point to i
				iarray.redirectFromTo(varray.count, i);
				

				//Log("%d and %d are duplicates. Redirecting all references of %d to %d.", i, j, j, i);

				j--;
			}
		}
	}

	Log("Done removing duplicated. Varray size: %d, IArray size %d", varray.count, iarray.indices.size());
}

NEPHILIM_NS_END