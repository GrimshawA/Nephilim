#include <Nephilim/World/AStaticMeshComponent.h>

#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

AStaticMeshComponent::AStaticMeshComponent()
{

}

/// Build directly with a static mesh geometry
AStaticMeshComponent::AStaticMeshComponent(StaticMesh* mesh)
{
	staticMesh.ptr = mesh;
}

/// Set a new static mesh to this instance
void AStaticMeshComponent::setStaticMesh(StaticMesh* mesh)
{
	staticMesh.ptr = mesh;
}

/// Add a new material to this mesh instance
void AStaticMeshComponent::addMaterial(const String& material)
{
	Material m(material);
	materials.push_back(m);
}

NEPHILIM_NS_END