#ifndef NephilimStaticMesh_h__
#define NephilimStaticMesh_h__

#include <Nephilim/Foundation/Asset.h>

#include <Nephilim/Graphics/Geometry.h>
#include <Nephilim/Graphics/VertexArray.h>
#include <Nephilim/Graphics/IndexArray.h>
#include <Nephilim/Graphics/VertexBuffer.h>
#include <Nephilim/Graphics/IndexBuffer.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API FStaticMeshVertexBuffer : public VertexBuffer
{
public:

};

class NEPHILIM_API FStaticMeshIndexBuffer : public IndexBuffer
{
public:

};

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
class NEPHILIM_API StaticMesh : public Asset
{
public:

	/// This is the vertex buffer resource for this static mesh (link to the uploaded GPU data)
	FStaticMeshVertexBuffer vertexBuffer;
	FStaticMeshIndexBuffer  indexBuffer;

	VertexArray clientData;

	String TEX; /// test tex for static meshes

public:
	
	/// Prepare our buffers with the given mesh
	void uploadGeometry(GeometryObject& object);

	// nice for prototyping stuff
	void makeDebugBox(float w, float h, float d);
};

NEPHILIM_NS_END
#endif // NephilimStaticMesh_h__
