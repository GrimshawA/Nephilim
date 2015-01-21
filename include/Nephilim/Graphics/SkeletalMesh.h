#ifndef NephilimGraphicsSkeletalMesh_h__
#define NephilimGraphicsSkeletalMesh_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/Math/Vectors.h>
#include <Nephilim/Graphics/VertexArray.h>
#include <Nephilim/Graphics/IndexArray.h>

NEPHILIM_NS_BEGIN

/**
	\class SkeletalMesh
	\brief A skeletal mesh resource, like a human body or creature with a rig for animation
*/
class NEPHILIM_API SkeletalMesh
{
public:
	VertexArray _vertexArray;
	IndexArray _indexArray;

	/// TODO, Need a way to "point" to a GPU vertex buffer so they can be rendered quickly
	// Agnostic to whether its a big Vertex buffer or an individual one
	//VertexBufferHandle handle;
public:

	/// Load the skeletal mesh from disk
	bool load(const String& filename);
};

NEPHILIM_NS_END
#endif // NephilimGraphicsSkeletalMesh_h__
