#ifndef NephilimRazerComponentTransform_h__
#define NephilimRazerComponentTransform_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Matrix.h>
#include <Nephilim/Razer/Component.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

/**
	\class ComponentTransform
	\brief 3D transform for a entity, scale + rotation + translation
*/
class NEPHILIM_API ComponentTransform : public Component
{
public:
	ComponentTransform()
	{
		x = y = z = 0.f;
	}

	float x, y, z;
	mat4 matrix;
};

};
NEPHILIM_NS_END
#endif // NephilimRazerComponentTransform_h__
