#include <Nephilim/Graphics/StaticMesh.h>
#include <Nephilim/Graphics/VertexArray.h>
#include <Nephilim/Graphics/GL/GLHelpers.h>


NEPHILIM_NS_BEGIN

/// Load the static mesh data from a file directly
bool StaticMesh::load(const String& filename)
{
	return geom.loadFromFile(filename);
}

void StaticMesh::makeDebugBox(float w, float h, float d)
{
	geom.addBox(w, h, d);
	geom.setAllColors(Color::White);
}


void StaticMesh::test()
{
	geom.addBox(1.f, 1.f, 1.f);
	geom.setAllColors(Color::White);
}

void StaticMesh::test2()
{
	geom.addCylinder();
	geom.setAllColors(Color::White);
}


NEPHILIM_NS_END