#ifndef NephilimRazerComponentSprite_h__
#define NephilimRazerComponentSprite_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/Strings.h>
#include <Nephilim/Razer/Component.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

/**
	\class ComponentSprite
	\brief 3D transform for a entity, scale + rotation + translation
*/
class NEPHILIM_API ComponentSprite : public Component
{
public:
	ComponentSprite();

	float width;
	float height;

	String tex;
	
	vec2 tex_rect_pos;
	vec2 tex_rect_size;

	vec2 scale;
};

};
NEPHILIM_NS_END

#endif // NephilimRazerComponentSprite_h__