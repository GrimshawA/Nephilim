#ifndef NephilimRazerComponentSprite_h__
#define NephilimRazerComponentSprite_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Color.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/Strings.h>
#include <Nephilim/Razer/Component.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

/**
	\class ComponentSprite
	\brief A sprite is basically a flat rectangle with a texture assigned to it
*/
class NEPHILIM_API ComponentSprite : public Component
{
public:
	/// Initialize the sprite with no area
	ComponentSprite();

	/// Set the size of the sprite
	void setSize(const vec2& s);

	/// Set the size of the sprite
	void setSize(float sx, float sy);

	/// Get the size of the sprite
	vec2 getSize();

	void setColor(int r, int g, int b);

	void setTextureRect(float x, float y, float w, float h);

	Color color;

	float width;
	float height;

	String tex;
	
	vec2 tex_rect_pos;
	vec2 tex_rect_size;

	vec2 scale;

	float rot = 0.f;
};

typedef ComponentSprite CSprite;

};
NEPHILIM_NS_END

#endif // NephilimRazerComponentSprite_h__