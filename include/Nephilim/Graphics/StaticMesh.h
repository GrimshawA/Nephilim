#ifndef NephilimMesh_h__
#define NephilimMesh_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Graphics/Geometry.h>
#include <Nephilim/Graphics/VertexArray.h>
#include <Nephilim/Graphics/IndexArray.h>

NEPHILIM_NS_BEGIN

/**
	\class StaticMesh
	\brief Holds geometry

	This class is only to store geometry of an object, which
	includes vertex positions, colors, texture coordinate sets
	and normals.

	This is the class used by the engine to actually store meshes
	in memory. Each mesh is a collection of triangles that use
	a single material (or layered material).

	Meshes are not aware of any material settings, which must be done externally,
	they simply represent a surface. 

	Meshes can be indexed or not (having arrays of indices to identify its faces)

	Supports multiple level of detail meshes. The renderer will pick a LOD level depending on the distance
	from the camera to the instance.
*/
class NEPHILIM_API StaticMesh
{
public:

	VertexArray _vertexArray;
	IndexArray _indexArray;

public:


	/// Load the static mesh data from a file directly
	bool load(const String& filename);

	void makeDebugBox(float w, float h, float d);

	GeometryData geom;

	void test();
	void test2();
};

NEPHILIM_NS_END
#endif // NephilimMesh_h__
