#include <Nephilim/SkinMesh.h>
#include <Nephilim/File.h>
#include <Nephilim/DataStream.h>

NEPHILIM_NS_BEGIN

/// Serializes this mesh into a file
bool SkinMesh::saveToFile(const String& filename)
{
	File outputFile(filename, IODevice::BinaryWrite);
	if(outputFile)
	{
		DataStream outputStream(outputFile);

		// Write the vertex list
		outputStream << static_cast<Int32>(mVertices.size());
		for(size_t i = 0; i < mVertices.size(); ++i)
		{
			outputStream << mVertices[i].position.x << mVertices[i].position.y << mVertices[i].position.z;
			outputStream << mVertices[i].uv.x       << mVertices[i].uv.y;
			outputStream << mVertices[i].normal.x   << mVertices[i].normal.y   << mVertices[i].normal.z;
			outputStream << mVertices[i].bones[0]   << mVertices[i].bones[1]   << mVertices[i].bones[3]     << mVertices[i].bones[4];
			outputStream << mVertices[i].weights[0] << mVertices[i].weights[1] << mVertices[i].weights[3]   << mVertices[i].weights[4];
		}

		// Write the face list (indices)
		outputStream << static_cast<Int32>(mFaces.size());
		for(size_t i = 0; i < mFaces.size(); ++i)
		{
			outputStream << mFaces[i];
		}

		return true;
	}
	else
	{
		return false;
	}
}

NEPHILIM_NS_END