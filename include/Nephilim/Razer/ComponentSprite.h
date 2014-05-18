#ifndef NephilimRazerComponentSprite_h__
#define NephilimRazerComponentSprite_h__

#include <Nephilim/Platform.h>
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
	float width;
	float height;
	String tex;
};

};
NEPHILIM_NS_END

#endif // NephilimRazerComponentSprite_h__