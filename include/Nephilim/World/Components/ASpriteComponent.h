#ifndef NephilimWorldActorSpriteComponent_h__
#define NephilimWorldActorSpriteComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/Components/ASceneComponent.h>

#include <Nephilim/Foundation/Vector.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/Foundation/Color.h>

NEPHILIM_NS_BEGIN

/**
	\class ASpriteComponent
	\brief A Sprite in the world
*/
class NEPHILIM_API ASpriteComponent : public ASceneComponent
{
public:
	/// Initialize the sprite with no area
	ASpriteComponent();

	/// Constructor with a texture name and size
	ASpriteComponent(vec2 size, const String& texture);

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
};

NEPHILIM_NS_END
#endif // NephilimWorldActorSpriteComponent_h__
