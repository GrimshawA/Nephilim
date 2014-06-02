#include <Nephilim/Razer/ComponentSprite.h>

NEPHILIM_NS_BEGIN
namespace rzr{

ComponentSprite::ComponentSprite()
: width(1.f)
, height(1.f)
, scale(1.f, 1.f)
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

};
NEPHILIM_NS_END