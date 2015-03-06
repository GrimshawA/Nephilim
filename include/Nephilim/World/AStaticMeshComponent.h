#ifndef NephilimWorldAStaticMeshComponent_h__
#define NephilimWorldAStaticMeshComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/ASceneComponent.h>

#include <Nephilim/Foundation/Vector.h>
#include <Nephilim/Graphics/StaticMesh.h>
#include <Nephilim/Game/Resource.h>

NEPHILIM_NS_BEGIN

/**
	\class AStaticMeshComponent
	\brief Place a static mesh in the world
*/

struct Material
{
	Material(const String& diffuseTexture)
	{
		diffuse = diffuseTexture;
	}

	String diffuse;
};

class NEPHILIM_API AStaticMeshComponent : public ASceneComponent
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
	AStaticMeshComponent();

	/// Build directly with a static mesh geometry
	AStaticMeshComponent(StaticMesh* mesh);

	/// Set a new static mesh to this instance
	void setStaticMesh(StaticMesh* mesh);

	/// Add a new material to this mesh instance
	void addMaterial(const String& material);
};

NEPHILIM_NS_END
#endif // NephilimWorldAStaticMeshComponent_h__
