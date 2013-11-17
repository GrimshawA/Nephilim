#ifndef NephilimSkinMesh_h__
#define NephilimSkinMesh_h__

#include "Platform.h"
#include "Vectors.h"
#include <vector>

NEPHILIM_NS_BEGIN

class String;

/**
	\class SkinMesh
	\brief 3D Model data
*/
class NEPHILIM_API SkinMesh
{
public:
	/// Serializes this mesh into a file
	bool saveToFile(const String& filename);

	class NEPHILIM_API SkinMeshVertex
	{
	public:
		vec3  position;   ///< Position of this vertex in model space
		vec2  uv;         ///< Texture coordinates
		vec3  normal;     ///< Normal of this vertex
		Int8  bones[4];   ///< Bone ID's of a max of 4 bones that can influence this vertex
		float weights[4]; ///< How much each bone can affect this vertex, 0.0 for no influence and 1.0 for full influence
	};

	std::vector<SkinMeshVertex> mVertices; ///< Vertices describing the mesh
	std::vector<Int16>          mFaces;    ///< Faces of the mesh (triangles)
};

NEPHILIM_NS_END
#endif // NephilimSkinMesh_h__
