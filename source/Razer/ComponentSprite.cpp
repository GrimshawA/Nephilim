#include <Nephilim/Razer/ComponentSprite.h>

NEPHILIM_NS_BEGIN
namespace rzr{

ComponentSprite::ComponentSprite()
: width(1.f)
, height(1.f)
, scale(1.f, 1.f)
, color(Color::White)
{

}

/// Set the size of the sprite
void ComponentSprite::setSize(const vec2& s)
{
	width = s.x;
	height = s.y;
}

/// Set the size of the sprite
void ComponentSprite::setSize(float sx, float sy)
{
	width = sx;
	height = sy;
}

/// Get the size of the sprite
vec2 ComponentSprite::getSize()
{
	return vec2(width, height);
}

void ComponentSprite::setTextureRect(float x, float y, float w, float h)
{
	tex_rect_pos.x = x;
	tex_rect_pos.y = y;
	tex_rect_size.x = w;
	tex_rect_size.y = h;
}

void ComponentSprite::setColor(int r, int g, int b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}


};
NEPHILIM_NS_END