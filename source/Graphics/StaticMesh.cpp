#include <Nephilim/Graphics/StaticMesh.h>
#include <Nephilim/VertexArray.h>
#include <Nephilim/CGL.h>


NEPHILIM_NS_BEGIN

/// Load the static mesh data from a file directly
bool StaticMesh::load(const String& filename)
{
	return geom.loadFromFile(filename);
}

void StaticMesh::test()
{
	geom.addBox(20.f, 20.f, 20.f);
	geom.setAllColors(Color::White);
}

void StaticMesh::test2()
{
	geom.addCylinder();
	geom.setAllColors(Color::White);
}


NEPHILIM_NS_END