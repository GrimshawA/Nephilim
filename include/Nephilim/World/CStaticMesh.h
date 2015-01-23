#ifndef NephilimRazerComponentMesh_h__
#define NephilimRazerComponentMesh_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Vector.h>
#include <Nephilim/Graphics/StaticMesh.h>
#include <Nephilim/Game/Resource.h>
#include <Nephilim/World/Component.h>

NEPHILIM_NS_BEGIN

/**
	\class CStaticMesh
	\brief Instance of a StaticMesh

	Each CStaticMesh is as small as possible, as they are potentially stored contiguously
	in memory, allowing for maximum compactness and speed, so the complex scene can be described with this.

	To avoid hurting the static mesh system performance, one should use actor components instead for very dynamic
	objects, as its components are kept separately.
*/

struct Material
{
	Material(const String& diffuseTexture)
	{
		diffuse = diffuseTexture;
	}

	String diffuse;
};

class NEPHILIM_API CStaticMesh : public Component
{
public:

	/// The static mesh this instance points to
	/// The resource smart pointer is used for reference counting the static mesh
	/// Renderers going through the scene components will use this variable to know what to render
	Resource<StaticMesh> staticMesh;

	/// Layered material list for this static mesh
	std::vector<Material> materials;

public:
	/// Default construction - doesn't render any mesh
	CStaticMesh();

	/// Build directly with a static mesh geometry
	CStaticMesh(StaticMesh* mesh);

	/// Set a new static mesh to this instance
	void setStaticMesh(StaticMesh* mesh);

	/// Add a new material to this mesh instance
	void addMaterial(const String& material);
};

NEPHILIM_NS_END

#endif // NephilimRazerComponentMesh_h__
