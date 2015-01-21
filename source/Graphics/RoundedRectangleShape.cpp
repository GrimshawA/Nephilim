#include <Nephilim/Graphics/RoundedRectangleShape.h>
#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/Graphics/CGL.h>
#include <Nephilim/Math/Math.h>

NEPHILIM_NS_BEGIN

RoundedRectangleShape::RoundedRectangleShape()
: m_geometryDirty(true)
, m_color(Color::White)
, m_outlineColor(Color::Black)
, m_cornerPointCount(5)
, m_radius(3.f)
, m_outlineThickness(0.f)
, m_topLeftRounded(true)
, m_topRightRounded(true)
, m_bottomLeftRounded(true)
, m_bottomRightRounded(true)
{
}

void RoundedRectangleShape::onDraw(GraphicsDevice* renderer)
{
	if(m_geometryDirty)
	{
		updateGeometry();
		m_geometryDirty = false;
	}

	renderer->setDefaultTexture();
	renderer->setModelMatrix(mat4(getTransform().getMatrix()));
	renderer->draw(m_geometry);
	glLineWidth(m_outlineThickness);
	renderer->draw(m_outline);
	renderer->setModelMatrix(mat4::identity);
}

void RoundedRectangleShape::setRadius(float radius)
{
	m_radius = radius;
	m_geometryDirty = true;
}

vec2 RoundedRectangleShape::getSize()
{
	return m_size;
}

vec2 RoundedRectangleShape::getFullSize()
{
	return vec2(m_size.x + m_radius * 2, m_size.y + m_radius*2);
}

void RoundedRectangleShape::setSize(float width, float height)
{
	m_size = vec2(width, height);
	m_geometryDirty = true;
}

void RoundedRectangleShape::setSize(vec2 size)
{
	m_size = size;
	m_geometryDirty = true;
}

void RoundedRectangleShape::setColor(const Color& color)
{
	m_color = color;
	m_geometryDirty = true;
}

void RoundedRectangleShape::setCornerPointCount(int count)
{
	m_cornerPointCount = count;
}

void RoundedRectangleShape::setCornerRounded(Corners corner, bool rounded)
{
	m_geometryDirty = true;

	switch(corner)
	{
	case TopLeft: m_topLeftRounded = rounded; break;
	case TopRight: m_topRightRounded = rounded; break;
	case BottomLeft: m_bottomLeftRounded = rounded; break;
	case BottomRight: m_bottomRightRounded = rounded; break;
	}
}

void RoundedRectangleShape::updateGeometry()
{
	m_geometry.clear();
	m_geometry.geometryType = Render::Primitive::Triangles;

	m_outline.clear();
	m_outline.geometryType = Render::Primitive::LineStrip;

	// Center
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x, m_size.y), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x, 0.f), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f, 0.f), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x, m_size.y), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f, 0.f), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f, m_size.y), m_color, vec2(0.f, 0.f)));

	// Left
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f, m_size.y), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f, 0.f), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(-m_radius, 0.f), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f, m_size.y), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(-m_radius, 0.f), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(-m_radius, m_size.y), m_color, vec2(0.f, 0.f)));

	// Right
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x + m_radius, m_size.y), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x + m_radius, 0.f), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x, 0.f), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x + m_radius, m_size.y), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x, 0.f), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x, m_size.y), m_color, vec2(0.f, 0.f)));

	// Top
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x, 0.f), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x, -m_radius), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f, -m_radius), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x, 0.f), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f, -m_radius), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f,  0.f), m_color, vec2(0.f, 0.f)));

	// Bottom
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x, m_size.y + m_radius), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x, m_size.y), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f, m_size.y), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x, m_size.y + m_radius), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f, m_size.y), m_color, vec2(0.f, 0.f)));
	m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f,  m_size.y + m_radius), m_color, vec2(0.f, 0.f)));

	m_outline.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f, -m_radius), m_outlineColor, vec2(0.f,0.f)));

	// Top left corner
	float angle = (math::pi / 2);
	float angle_increment = (math::pi / 2) / m_cornerPointCount;
	for(int i = 0; i < m_cornerPointCount; ++i)
	{
		m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f, 0.f), m_color, vec2(0.f, 0.f)));
		m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(cos(angle) * m_radius, -sin(angle) * m_radius), m_color, vec2(0.f, 0.f)));
		m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(cos(angle + angle_increment) * m_radius, -sin(angle + angle_increment) * m_radius), m_color, vec2(0.f, 0.f)));
		
		m_outline.m_vertices.push_back(VertexArray2D::Vertex(vec2(cos(angle + angle_increment) * m_radius, -sin(angle + angle_increment) * m_radius), m_outlineColor, vec2(0.f,0.f)));

		angle += angle_increment;
	}

	m_outline.m_vertices.push_back(VertexArray2D::Vertex(vec2(-m_radius, m_size.y), m_outlineColor, vec2(0.f,0.f)));

	////////////////////////////////////////////////////////////////////////// BOTTOM LEFT
	if(m_bottomLeftRounded) // -- Bottom left is rounded
	{
		// Bottom left corner
		for(int i = 0; i < m_cornerPointCount; ++i)
		{
			m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f, m_size.y), m_color, vec2(0.f, 0.f)));
			m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(cos(angle) * m_radius, m_size.y + -sin(angle) * m_radius), m_color, vec2(0.f, 0.f)));
			m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(cos(angle + angle_increment) * m_radius, m_size.y + -sin(angle + angle_increment) * m_radius), m_color, vec2(0.f, 0.f)));

			m_outline.m_vertices.push_back(VertexArray2D::Vertex(vec2(cos(angle + angle_increment) * m_radius, m_size.y + -sin(angle + angle_increment) * m_radius), m_outlineColor, vec2(0.f,0.f)));

			angle += angle_increment;
		}	
	}
	else // -- Bottom left is just a square
	{
		angle += math::pi / 2.f;

		m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f, m_size.y + m_radius), m_color, vec2(0.f, 0.f)));
		m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f, m_size.y), m_color, vec2(0.f, 0.f)));
		m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(-m_radius, m_size.y), m_color, vec2(0.f, 0.f)));
		m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f, m_size.y + m_radius), m_color, vec2(0.f, 0.f)));
		m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(-m_radius, m_size.y), m_color, vec2(0.f, 0.f)));
		m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(-m_radius, m_size.y + m_radius), m_color, vec2(0.f, 0.f)));

		m_outline.m_vertices.push_back(VertexArray2D::Vertex(vec2(-m_radius, m_size.y + m_radius), m_outlineColor, vec2(0.f,0.f)));
		m_outline.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f, m_size.y + m_radius), m_outlineColor, vec2(0.f,0.f)));
	}
	// Bottom outline
	m_outline.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x, m_size.y + m_radius), m_outlineColor, vec2(0.f,0.f)));

	////////////////////////////////////////////////////////////////////////// BOTTOM RIGHT

	if(m_bottomRightRounded)
	{
		// Bottom right corner
		for(int i = 0; i < m_cornerPointCount; ++i)
		{
			m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x, m_size.y), m_color, vec2(0.f, 0.f)));
			m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x + cos(angle) * m_radius, m_size.y + -sin(angle) * m_radius), m_color, vec2(0.f, 0.f)));
			m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x + cos(angle + angle_increment) * m_radius, m_size.y + -sin(angle + angle_increment) * m_radius), m_color, vec2(0.f, 0.f)));

			m_outline.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x + cos(angle + angle_increment) * m_radius, m_size.y + -sin(angle + angle_increment) * m_radius), m_outlineColor, vec2(0.f,0.f)));

			angle += angle_increment;
		}
	}
	else
	{
		angle += math::pi / 2.f;

		m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x + m_radius, m_size.y + m_radius), m_color, vec2(0.f, 0.f)));
		m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x + m_radius, m_size.y), m_color, vec2(0.f, 0.f)));
		m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x, m_size.y), m_color, vec2(0.f, 0.f)));
		m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x + m_radius, m_size.y + m_radius), m_color, vec2(0.f, 0.f)));
		m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x, m_size.y), m_color, vec2(0.f, 0.f)));
		m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x, m_size.y + m_radius), m_color, vec2(0.f, 0.f)));

		m_outline.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x + m_radius, m_size.y + m_radius), m_outlineColor, vec2(0.f,0.f)));
		m_outline.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x + m_radius, m_size.y), m_outlineColor, vec2(0.f,0.f)));
	}


	// Right outline
	m_outline.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x + m_radius, 0.f), m_outlineColor, vec2(0.f,0.f)));

	// Top right corner
	for(int i = 0; i < m_cornerPointCount; ++i)
	{
		m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x, 0.f), m_color, vec2(0.f, 0.f)));
		m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x + cos(angle) * m_radius, -sin(angle) * m_radius), m_color, vec2(0.f, 0.f)));
		m_geometry.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x + cos(angle + angle_increment) * m_radius, -sin(angle + angle_increment) * m_radius), m_color, vec2(0.f, 0.f)));

		m_outline.m_vertices.push_back(VertexArray2D::Vertex(vec2(m_size.x + cos(angle + angle_increment) * m_radius, -sin(angle + angle_increment) * m_radius), m_outlineColor, vec2(0.f,0.f)));

		angle += angle_increment;
	}

	// Top outline
	m_outline.m_vertices.push_back(VertexArray2D::Vertex(vec2(0.f, -m_radius), m_outlineColor, vec2(0.f,0.f)));
}

void RoundedRectangleShape::setOutlineThickness(float thickness)
{
	m_outlineThickness = thickness;
}

void RoundedRectangleShape::setOutlineColor(const Color& outlineColor)
{
	m_outlineColor = outlineColor;
	m_geometryDirty = true;
}

NEPHILIM_NS_END