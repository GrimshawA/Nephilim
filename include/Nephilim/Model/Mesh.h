#ifndef NephilimMesh_h__
#define NephilimMesh_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class Mesh
	\brief Contains geometry

	This class is only to store geometry of an object, which
	includes vertex positions, colors, texture coordinate sets
	and normals.

	This is the class used by the engine to actually store meshes
	in memory. Each mesh is a collection of triangles that use
	a single material (or layered material).

	Meshes are not aware of any material settings, which must be done externally,
	they simply represent a surface. 

	Meshes can be indexed or not (having arrays of indices to identify its faces)
*/
class NEPHILIM_API Mesh
{
public:

};

NEPHILIM_NS_END
#endif // NephilimMesh_h__
