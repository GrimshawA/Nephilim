#include <Nephilim/World/ASpriteComponent.h>
#include <Nephilim/World/World.h>

#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Foundation/Math.h>

NEPHILIM_NS_BEGIN

ASpriteComponent::ASpriteComponent()
: width(1.f)
, height(1.f)
, color(Color::White)
, scale(1.f, -1.f)
{
	setPosition(math::randomInt(0, 1000), math::randomInt(0, 1000), 0.f);
	setSize(300.f, 300.f);

	color.r = math::randomInt(0, 100);
}

/// Constructor with a texture name and size
ASpriteComponent::ASpriteComponent(vec2 size, const String& texture)
: width(size.x)
, height(size.y)
, color(Color::White)
, tex(texture)
, scale(1.f, -1.f)
{

}

/// Set the size of the sprite
void ASpriteComponent::setSize(const vec2& s)
{
	width = s.x;
	height = s.y;
}

/// Set the size of the sprite
void ASpriteComponent::setSize(float sx, float sy)
{
	width = sx;
	height = sy;
}

/// Get the size of the sprite
vec2 ASpriteComponent::getSize()
{
	return vec2(width, height);
}

void ASpriteComponent::setTextureRect(float x, float y, float w, float h)
{
	tex_rect_pos.x = x;
	tex_rect_pos.y = y;
	tex_rect_size.x = w;
	tex_rect_size.y = h;
}

void ASpriteComponent::setColor(int r, int g, int b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}

NEPHILIM_NS_END