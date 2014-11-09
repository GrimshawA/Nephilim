#ifndef NephilimRazerComponentMesh_h__
#define NephilimRazerComponentMesh_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Vectors.h>

#include <Nephilim/VertexArray.h>
#include <Nephilim/IndexArray.h>

#include <Nephilim/Graphics/VertexBuffer.h>
#include <Nephilim/Graphics/IndexBuffer.h>

#include <Nephilim/Razer/Component.h>

NEPHILIM_NS_BEGIN

class Tilemap;

namespace rzr {

/**
	\class CMesh
	\brief Component: static mesh for manipulating and displaying a geometry
*/
class NEPHILIM_API CMesh : public Component
{
public:
	CMesh();

	bool loadCubesFromTilemap(Tilemap* tilemap);

	VertexArray mVertexArray;
	IndexArray  mIndexArray;

	VertexBuffer mVertexBuffer; ///< GPU-side geometry
	IndexBuffer  mIndexBuffer;  ///< GPU-side geometry
};

};
NEPHILIM_NS_END

#endif // NephilimRazerComponentMesh_h__
