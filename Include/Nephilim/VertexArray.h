#ifndef PARABOLA_VERTEXARRAYS_H
#define PARABOLA_VERTEXARRAYS_H

#include "Platform.h"
#include "Vectors.h"
#include "Rect.h"
#include <vector>
#include "Color.h"

PARABOLA_NAMESPACE_BEGIN

enum PrimitiveType{
	Triangles = 0,
	TriangleFan
};

class PARABOLA_API Vertex{
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

class PARABOLA_API VertexArray{
public:
	/// Constructs an empty vertex array with default primitive type - Quads
	VertexArray();

	VertexArray(PrimitiveType primitiveType, unsigned int vertexCount);

	/// Compute the bounds from the points in the array
	FloatRect getBounds();

	/// Clear the contents of the vertex array
	void clear();

	/// Append the vertex v to the current list
	void append(const Vertex& v);


	Vertex& operator[](unsigned int index);

	std::vector<Vertex> m_vertices;

	PrimitiveType geometryType;
};

PARABOLA_NAMESPACE_END
#endif