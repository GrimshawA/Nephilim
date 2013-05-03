#include <Nephilim/CircleShape.h>
#include <Nephilim/Renderer.h>

NEPHILIM_NS_BEGIN

CircleShape::CircleShape()
: m_radius(1.f)
, m_pointCount(30.f)
, m_fillColor(Color::Orange)
{
	update();
}


void CircleShape::onDraw(Renderer* renderer)
{
	renderer->setDefaultTexture();
	renderer->setModelMatrix(mat4(getTransform().getMatrix()));
	renderer->draw(m_vertices);
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
	m_vertices.geometryType = Render::Primitive::TriangleFan;

	const float k_segments = m_pointCount;
	const float k_increment = 2.0f * 3.14159 / k_segments;
	float theta = 0.0f;

	for (int i = 0; i < k_segments; ++i)
	{
		Vec2f v = Vec2f(cosf(theta), sinf(theta)) * m_radius;
		theta += k_increment;
		m_vertices.append(VertexArray2D::Vertex(v, m_fillColor, Vec2f()));
	}
}



NEPHILIM_NS_END