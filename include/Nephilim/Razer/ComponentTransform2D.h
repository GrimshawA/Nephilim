#ifndef NephilimRazerComponentTransform2D_h__
#define NephilimRazerComponentTransform2D_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Razer/Component.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

/**
	\class ComponentTransform
	\brief 3D transform for a entity, scale + rotation + translation
*/
class NEPHILIM_API ComponentTransform2D : public Component
{
public:
	float x, y;
	float rotation;
	float scale_x;
	float scale_y;
};

};
NEPHILIM_NS_END

#endif // NephilimRazerComponentTransform2D_h__
