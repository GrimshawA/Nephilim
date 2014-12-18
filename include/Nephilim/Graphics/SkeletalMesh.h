#ifndef NephilimGraphicsSkeletalMesh_h__
#define NephilimGraphicsSkeletalMesh_h__

#include <Nephilim/Platform.h>
#include <Nephilim/VertexArray.h>
#include <Nephilim/IndexArray.h>

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
};

NEPHILIM_NS_END
#endif // NephilimGraphicsSkeletalMesh_h__
