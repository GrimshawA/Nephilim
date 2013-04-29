#include <Nephilim/VertexArray2D.h>

NEPHILIM_NS_BEGIN

/// Constructs an empty vertex array with default primitive type - Quads
VertexArray2D::VertexArray2D()
: m_textured(false){
	geometryType = Render::Primitive::TriangleFan;
};

VertexArray2D::VertexArray2D(Render::Primitive::Type primitiveType, unsigned int vertexCount)
: m_textured(false){
	geometryType = primitiveType;
	m_vertices.resize(vertexCount);
};

VertexArray2D::Vertex& VertexArray2D::operator[](unsigned int index){
	return m_vertices[index];
};

/// Compute the bounds from the points in the array
FloatRect VertexArray2D::getBounds(){
	if (!m_vertices.empty())
	{
		float left   = m_vertices[0].position.x;
		float top    = m_vertices[0].position.y;
		float right  = m_vertices[0].position.x;
		float bottom = m_vertices[0].position.y;

		for (std::size_t i = 0; i < m_vertices.size(); ++i)
		{
			Vec2f position = m_vertices[i].position;

			// Update left and right
			if (position.x < left)
				left = position.x;
			else if (position.x > right)
				right = position.x;

			// Update top and bottom
			if (position.y < top)
				top = position.y;
			else if (position.y > bottom)
				bottom = position.y;
		}

		return FloatRect(left, top, right - left, bottom - top);
	}
	else
	{
		// Array is empty
		return FloatRect();
	}
};

/// Append the vertex v to the current list
void VertexArray2D::append(const Vertex& v){
	m_vertices.push_back(v);
};

/// Clear the contents of the vertex array
void VertexArray2D::clear(){
	m_vertices.clear();
}

NEPHILIM_NS_END