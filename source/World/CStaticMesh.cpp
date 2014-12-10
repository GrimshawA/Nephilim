#include <Nephilim/World/CStaticMesh.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

CStaticMesh::CStaticMesh()
{

}

/// Build directly with a static mesh geometry
CStaticMesh::CStaticMesh(StaticMesh* mesh)
{
	staticMesh.ptr = mesh;
}

/// Set a new static mesh to this instance
void CStaticMesh::setStaticMesh(StaticMesh* mesh)
{
	staticMesh.ptr = mesh;
}

NEPHILIM_NS_END