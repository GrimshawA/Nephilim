#include <Nephilim/Graphics/StaticMesh.h>
#include <Nephilim/Graphics/VertexArray.h>
#include <Nephilim/Graphics/GL/GLHelpers.h>


#include <Nephilim/Graphics/GL/GLVertexBuffer.h>


NEPHILIM_NS_BEGIN

/// Prepare our buffers with the given mesh
void StaticMesh::uploadGeometry(const GeometryObject& object)
{
	object.toVertexArray(clientData);

	vertexBuffer._impl = new GLVertexBuffer();

	GLVertexBuffer* vbo = (GLVertexBuffer*)vertexBuffer._impl;
	vbo->create();
	vbo->bind();
	vbo->upload(clientData, GLVertexBuffer::StaticDraw);
}

void StaticMesh::makeDebugBox(float w, float h, float d)
{
	GeometryObject ourBoxGeomData;
	ourBoxGeomData.addBox(w, h, d);
	ourBoxGeomData.generateNormals();
	ourBoxGeomData.setAllColors(Color::Red);

	for (auto& v : ourBoxGeomData.vertices)
	{
		v.x += w / 2.f;
	}

	//IndexArray indexes; 
	ourBoxGeomData.toVertexArray(clientData);
	//VertexArray::removeDuplicateVertices(ourBoxGeom, indexes);

	vertexBuffer._impl = new GLVertexBuffer();
	
	GLVertexBuffer* vbo = (GLVertexBuffer*)vertexBuffer._impl;
	vbo->create();
	vbo->bind();
	vbo->upload(clientData, GLVertexBuffer::StaticDraw);
}

NEPHILIM_NS_END