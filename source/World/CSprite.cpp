#include <Nephilim/World/CSprite.h>

NEPHILIM_NS_BEGIN
namespace rzr{

CSprite::CSprite()
: width(1.f)
, height(1.f)
, color(Color::White)
, scale(1.f, -1.f)
{

}

/// Constructor with a texture name and size
CSprite::CSprite(vec2 size, const String& texture)
: width(size.x)
, height(size.y)
, color(Color::White)
, tex(texture)
, scale(1.f, -1.f)
{

}

/// Set the size of the sprite
void CSprite::setSize(const vec2& s)
{
	width = s.x;
	height = s.y;
}

/// Set the size of the sprite
void CSprite::setSize(float sx, float sy)
{
	width = sx;
	height = sy;
}

/// Get the size of the sprite
vec2 CSprite::getSize()
{
	return vec2(width, height);
}

void CSprite::setTextureRect(float x, float y, float w, float h)
{
	tex_rect_pos.x = x;
	tex_rect_pos.y = y;
	tex_rect_size.x = w;
	tex_rect_size.y = h;
}

void CSprite::setColor(int r, int g, int b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}


};
NEPHILIM_NS_END