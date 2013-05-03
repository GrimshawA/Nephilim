#include <Nephilim/CircleShape.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/CGL.h>

NEPHILIM_NS_BEGIN

CircleShape::CircleShape()
: m_radius(1.f)
, m_pointCount(30.f)
, m_fillColor(Color::Orange)
, m_outlineColor(Color::Black)
, m_outlineThickness(1.f)
{
	update();
}


void CircleShape::onDraw(Renderer* renderer)
{
	renderer->setDefaultTexture();
	renderer->setModelMatrix(mat4(getTransform().getMatrix()));
	renderer->draw(m_vertices);
	glLineWidth(m_outlineThickness);
	renderer->draw(m_outlineGeometry);
	renderer->setModelMatrix(mat4());
}
void CircleShape::setPointCount(int segmentCount)
{
	m_pointCount = segmentCount;
	update();
}

void CircleShape::setFillColor(Color color)
{
	m_fillColor = color;
	update();
}

void CircleShape::setRadius(float radius)
{
	m_radius = radius;
	update();
}

void CircleShape::update()
{
	m_vertices.clear();
	m_outlineGeometry.clear();
	m_vertices.geometryType = Render::Primitive::TriangleFan;
	m_outlineGeometry.geometryType = Render::Primitive::LineLoop;

	const float k_segments = m_pointCount;
	const float k_increment = 2.0f * 3.14159 / k_segments;
	float theta = 0.0f;

	for (int i = 0; i < k_segments; ++i)
	{
		Vec2f v = Vec2f(cosf(theta), sinf(theta)) * m_radius;
		theta += k_increment;
		m_vertices.append(VertexArray2D::Vertex(v, m_fillColor, Vec2f()));
		m_outlineGeometry.append(VertexArray2D::Vertex(v, m_outlineColor, Vec2f()));
	}
}

void CircleShape::setOutlineThickness(float thickness)
{
	m_outlineThickness = thickness;
	update();
}

void CircleShape::setOutlineColor(Color color)
{
	m_outlineColor = color;
	update();
}



NEPHILIM_NS_END