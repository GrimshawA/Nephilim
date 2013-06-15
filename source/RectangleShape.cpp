#include <Nephilim/RectangleShape.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/Texture.h>

#include <cmath>

NEPHILIM_NS_BEGIN

RectangleShape::RectangleShape()
: m_geometry(Render::Primitive::TriangleFan, 4)
, m_texture(NULL)
{
	m_geometry[0].position = vec2(0.f,0.f);
	m_geometry[1].position = vec2(1.f,0.f);
	m_geometry[2].position = vec2(1.f,1.f);
	m_geometry[3].position = vec2(0.f,1.f);

	m_geometry[0].texCoords = vec2(0.f, 0.f);
	m_geometry[1].texCoords = vec2(1.f, 0.f);
	m_geometry[2].texCoords = vec2(1.f, 1.f);
	m_geometry[3].texCoords = vec2(0.f, 1.f);

	// Default white color
	m_geometry[0].color = Color::White;
	m_geometry[1].color = Color::White;
	m_geometry[2].color = Color::White;
	m_geometry[3].color = Color::White;
}

void RectangleShape::setSize(const vec2& size)
{
	float width = size.x;
	float height = size.y;
	m_geometry[0].position = Vec2f(0.f,0.f);
	m_geometry[1].position = Vec2f(width,0.f);
	m_geometry[2].position = Vec2f(width,height);
	m_geometry[3].position = Vec2f(0.f,height);
}

/// Get the size of the rectangle
vec2 RectangleShape::getSize()
{
	return vec2(m_geometry[2].position.x, m_geometry[2].position.y);
}

/// Invert the vertical coordinates of the texture - hacky
void RectangleShape::invertTextureCoordinates()
{
	m_geometry[0].texCoords = vec2(m_geometry[0].texCoords.x, fabs(m_geometry[0].texCoords.y - 1.f));
	m_geometry[1].texCoords = vec2(m_geometry[1].texCoords.x, fabs(m_geometry[1].texCoords.y - 1.f));
	m_geometry[2].texCoords = vec2(m_geometry[2].texCoords.x, fabs(m_geometry[2].texCoords.y - 1.f));
	m_geometry[3].texCoords = vec2(m_geometry[3].texCoords.x, fabs(m_geometry[3].texCoords.y - 1.f));
}

void RectangleShape::setSize(float width, float height)
{
	m_geometry[0].position = Vec2f(0.f,0.f);
	m_geometry[1].position = Vec2f(width,0.f);
	m_geometry[2].position = Vec2f(width,height);
	m_geometry[3].position = Vec2f(0.f,height);
}

void RectangleShape::setTexture(Texture* texture)
{
	if(texture)
	{
		m_geometry.m_textured = true;
		m_texture = texture;
	}
	else
	{
		m_geometry.m_textured = false;
		m_texture = NULL;
	}
}

void RectangleShape::setColor(const Color& color)
{
	m_geometry[0].color = color;
	m_geometry[1].color = color;
	m_geometry[2].color = color;
	m_geometry[3].color = color;
}

void RectangleShape::setColors(const Color& topleft, const Color& topright, const Color& bottomright, const Color& bottomleft)
{
	m_geometry[0].color = topleft;
	m_geometry[1].color = topright;
	m_geometry[2].color = bottomright;
	m_geometry[3].color = bottomleft;
}

/// Set the sub region of the texture to display. These coordinates are in pixels and are normalized internally
void RectangleShape::setTextureRect(float left, float top, float width, float height)
{
	if(!m_texture) return;

	m_geometry[0].texCoords = vec2(left / m_texture->getSize().x, top / m_texture->getSize().y);
	m_geometry[1].texCoords = vec2((left + width) / m_texture->getSize().x , top / m_texture->getSize().y);
	m_geometry[2].texCoords = vec2((left + width) / m_texture->getSize().x, (top + height) / m_texture->getSize().y);
	m_geometry[3].texCoords = vec2(left / m_texture->getSize().x, (top + height) / m_texture->getSize().y);
}

void RectangleShape::onDraw(Renderer* renderer)
{
	if(m_texture) m_texture->bind();
	else renderer->setDefaultTexture();
	renderer->setModelMatrix(mat4(getTransform().getMatrix()));
	renderer->draw(m_geometry);
	renderer->setModelMatrix(mat4::identity);
	renderer->setDefaultTexture();
}

NEPHILIM_NS_END