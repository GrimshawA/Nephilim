#include <Nephilim/Graphics/RectangleShape.h>
#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/Graphics/GLTexture.h>
#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Graphics/CGL.h>

#include <cmath>

NEPHILIM_NS_BEGIN

RectangleShape::RectangleShape()
: m_geometry(Render::Primitive::TriangleFan, 4)
, m_outline(Render::Primitive::Lines, 8)
, m_texture(NULL)
, m_width(1.f)
, m_height(1.f)
, m_outlineThickness(1.f)
{
	initialize();
}

RectangleShape::RectangleShape(FloatRect rect, Color color)
: m_geometry(Render::Primitive::TriangleFan, 4)
, m_outline(Render::Primitive::Lines, 8)
, m_texture(NULL)
, m_width(1.f)
, m_height(1.f)
, m_outlineThickness(1.f)
{
	initialize();

	setPosition(rect.left, rect.top);
	setSize(rect.width, rect.height);
	setColor(color);
}

void RectangleShape::initialize()
{
	m_geometry[0].position = vec2(0.f,0.f);
	m_geometry[1].position = vec2(1.f,0.f);
	m_geometry[2].position = vec2(1.f,1.f);
	m_geometry[3].position = vec2(0.f,1.f);

	m_geometry[0].texCoords = vec2(0.f, 0.f);
	m_geometry[1].texCoords = vec2(1.f, 0.f);
	m_geometry[2].texCoords = vec2(1.f, 1.f);
	m_geometry[3].texCoords = vec2(0.f, 1.f);

	m_geometry.m_textured = false;

	// Default white color
	m_geometry[0].color = Color::White;
	m_geometry[1].color = Color::White;
	m_geometry[2].color = Color::White;
	m_geometry[3].color = Color::White;

	setOutlineColor(Color(91,91,91,0));

	updateInternalOutline();
}

void RectangleShape::updateInternalOutline()
{
	m_outline[0].position = vec2(0.f,0.f);
	m_outline[1].position = vec2(m_width,0.f);

	m_outline[2].position = vec2(m_width,0.f);
	m_outline[3].position = vec2(m_width,m_height);

	m_outline[4].position = vec2(m_width,m_height);
	m_outline[5].position = vec2(0.f,m_height);

	m_outline[6].position = vec2(0.f,0.f);
	m_outline[7].position = vec2(0.f,m_height);
}

void RectangleShape::setRect(FloatRect rect)
{
	setPosition(rect.left, rect.top);
	setSize(rect.width, rect.height);
}

void RectangleShape::setOutlineThickness(float thickness)
{
	m_outlineThickness = thickness;
}

void RectangleShape::setSize(const vec2& size)
{
	float width = size.x;
	float height = size.y;
	m_width = width;
	m_height = height;
	m_geometry[0].position = Vec2f(0.f,0.f);
	m_geometry[1].position = Vec2f(width,0.f);
	m_geometry[2].position = Vec2f(width,height);
	m_geometry[3].position = Vec2f(0.f,height);

	updateInternalOutline();
}

/// Get the size of the rectangle
vec2 RectangleShape::getSize() const
{
	return vec2(m_geometry.m_vertices[2].position.x, m_geometry.m_vertices[2].position.y);
}

void RectangleShape::setOutlineColor(const Color& outlineColor)
{
	for(int i = 0; i < m_outline.m_vertices.size(); ++i)
	{
		m_outline[i].color = outlineColor;
	}
}

/// Check if a given point lies inside the shape
bool RectangleShape::contains(vec2 point) const
{
	vec2 fpoint = getInverseTransform().transformPoint(point);
//	Log("(%f,%f) -> (%f, %f)", point.x, point.y, fpoint.x, fpoint.y);

	return ((fpoint.x >= 0.f) 
		&& (fpoint.x <= m_width)
		&& (fpoint.y >= 0 )
		&& (fpoint.y <= m_height));
}

bool RectangleShape::intersects(const RectangleShape& rect)
{
	// -- Check if any of rect's points are within my rect
	vec2 topLeft = rect.getTransform().transformPoint(vec2(0.f, 0.f));
	vec2 topRight = rect.getTransform().transformPoint(vec2(rect.getSize().x, 0.f));
	vec2 bottomLeft = rect.getTransform().transformPoint(vec2(0.f, rect.getSize().y));
	vec2 bottomRight = rect.getTransform().transformPoint(vec2(rect.getSize().x, rect.getSize().y));

	vec2 mtopLeft = getTransform().transformPoint(vec2(0.f, 0.f));
	vec2 mtopRight = getTransform().transformPoint(vec2(getSize().x, 0.f));
	vec2 mbottomLeft = getTransform().transformPoint(vec2(0.f, getSize().y));
	vec2 mbottomRight = getTransform().transformPoint(vec2(getSize().x, getSize().y));

	return (contains(topLeft) || contains(topRight) || contains(bottomLeft) || contains(bottomRight) ||
		    rect.contains(mtopLeft) || rect.contains(mtopRight) || rect.contains(mbottomLeft) || rect.contains(mbottomRight));
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
	m_width = width;
	m_height = height;

	updateInternalOutline();
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

	//Log("Setting coords");
}

/// Set the sub region of the texture to display. These coordinates are in pixels and are normalized internally
void RectangleShape::setTextureRect(FloatRect rect)
{
	setTextureRect(rect.left, rect.top, rect.width, rect.height);
}

void RectangleShape::onDraw(GraphicsDevice* renderer)
{
	if(m_texture) m_texture->bind();
	else renderer->setDefaultTexture();

	if (useOwnTransform)
		renderer->setModelMatrix(mat4(getTransform().getMatrix()));
	
	renderer->draw(m_geometry);
	if(m_outlineThickness > 0.f)
	{
		renderer->setDefaultTexture();
		glLineWidth(m_outlineThickness);
		renderer->draw(m_outline);
		renderer->setModelMatrix(mat4::identity);
	}	
	renderer->setDefaultTexture();
}

NEPHILIM_NS_END