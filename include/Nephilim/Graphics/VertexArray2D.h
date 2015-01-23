#ifndef VertexArray_h__
#define VertexArray_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Vector.h>
#include <Nephilim/Foundation/Rect.h>
#include <Nephilim/Foundation/Color.h>
#include <Nephilim/Graphics/RenderModes.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\ingroup Graphics
	\class VertexArray2D
	\brief Small and focused geometry container

	VertexArray2D is a simple class to compose 2D geometry. 
	It allows you to make objects with position, color and texture coordinates only.

	You can draw geometry in VertexArray2D with Renderer::draw directly.
*/
class NEPHILIM_API VertexArray2D
{
public:

	/// \ingroup Graphics
	/// \class Vertex
	/// \brief Represents one unique vertex
	/// Vertices are composed by a 2D position, a Color and a UV coordinate. This representation is exclusive to VertexArray2D usage.
	class NEPHILIM_API Vertex{
	public:
		Vertex(){}

		Vertex(Vec2f pos, Color col, Vec2f tex){
			position = pos;
			color = col;
			texCoords = tex;
		}

		Vec2f position;
		Color color;
		Vec2f texCoords;
	};

	/// Constructs an empty vertex array with default primitive type - Quads
	VertexArray2D();

	VertexArray2D(Render::Primitive::Type primitiveType, unsigned int vertexCount);

	/// Compute the bounds from the points in the array
	FloatRect getBounds();

	/// Clear the contents of the vertex array
	void clear();

	/// Append the vertex v to the current list
	void append(const Vertex& v);


	Vertex& operator[](unsigned int index);

	std::vector<Vertex> m_vertices;
	bool m_textured;

	Render::Primitive::Type geometryType;
};

NEPHILIM_NS_END
#endif // VertexArray_h__
