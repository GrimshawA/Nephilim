#include <Nephilim/Graphics/CircleShape.h>
#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/CGL.h>
#include <Nephilim/Logger.h>
#include <Nephilim/Math/Math.h>

NEPHILIM_NS_BEGIN

CircleShape::CircleShape()
: m_radius(1.f)
, m_pointCount(30.f)
, m_fillColor(Color::Orange)
, m_outlineColor(Color::Black)
, m_outlineThickness(0.f)
, m_beginAngle(0.f)
, m_spanAngle(math::pi * 2)
, m_texture(NULL)
, m_textureRadius(0.f)
, m_textureOrigin(0.f, 0.f)
, isDirty(false)
{
	
}

void CircleShape::setTexture(Texture* texture)
{
	m_texture = texture;
}

void CircleShape::setTextureCoords(float origin_x, float origin_y, float radius)
{
	m_textureOrigin.x = origin_x;
	m_textureOrigin.y = origin_y;
	m_textureRadius = radius;

	if(m_texture)
	{
		// normalize the center
		m_textureOrigin.x /= m_texture->getSize().x;
		m_textureOrigin.y /= m_texture->getSize().y;
	}
}

void CircleShape::onDraw(GraphicsDevice* renderer)
{
	if(isDirty)
		update();
	
	if(m_texture)
	{
		m_texture->bind();
	}
	else
	{
		renderer->setDefaultTexture();
	}
	renderer->setModelMatrix(mat4(getTransform().getMatrix()));
	renderer->draw(m_vertices);
	if(m_outlineThickness > 0.f)
	{
		glLineWidth(m_outlineThickness);
		renderer->draw(m_outlineGeometry);
	}	
	renderer->setModelMatrix(mat4());
}
void CircleShape::setPointCount(int segmentCount)
{
	m_pointCount = segmentCount;
	isDirty = true;
}

void CircleShape::setFillColor(Color color)
{
	m_fillColor = color;
	isDirty = true;
}

void CircleShape::setRadius(float radius)
{
	m_radius = radius;
	isDirty = true;
}

void CircleShape::update()
{
	m_vertices.clear();
	m_outlineGeometry.clear();
	m_vertices.geometryType = Render::Primitive::TriangleFan;
	m_outlineGeometry.geometryType = Render::Primitive::LineLoop;

	//Log("origin %f %f", m_textureOrigin.x, m_textureOrigin.y);

	m_vertices.append(VertexArray2D::Vertex(vec2(0.f,0.f), m_fillColor, m_textureOrigin));

	const float k_segments = m_pointCount;
	const float k_increment = m_spanAngle / k_segments;

	float theta = m_beginAngle;

	for (int i = 0; i <= k_segments; ++i)
	{
		Vec2f v = Vec2f(cosf(theta), sinf(theta)) * m_radius;
		theta += k_increment;
		if(m_texture)
		{
			m_vertices.append(VertexArray2D::Vertex(v, m_fillColor, vec2(m_textureOrigin.x + cosf(theta) * (m_textureRadius / m_texture->getSize().x), m_textureOrigin.y + sinf(theta) * (m_textureRadius / m_texture->getSize().y))));
		}
		else
		{
			m_vertices.append(VertexArray2D::Vertex(v, m_fillColor, vec2()));
		}

		m_outlineGeometry.append(VertexArray2D::Vertex(v, m_outlineColor, Vec2f()));
	}

	isDirty = false;
}

void CircleShape::setOutlineThickness(float thickness)
{
	m_outlineThickness = thickness;
	isDirty = true;
}

void CircleShape::setOutlineColor(Color color)
{
	m_outlineColor = color;
	isDirty = true;
}

NEPHILIM_NS_END