#ifndef NephilimRazerComponentCamera_h__
#define NephilimRazerComponentCamera_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/Razer/Component.h>

NEPHILIM_NS_BEGIN
namespace rzr {

/**
	\class ComponentCamera
	\brief 
*/
class NEPHILIM_API ComponentCamera : public Component
{
public:
	ComponentCamera();

	vec3 position;
	vec3 eye;
	vec3 up;

	float x,y,z; // where the camera is
	float center_x, center_y, center_z;
};

};
NEPHILIM_NS_END
#endif // NephilimRazerComponentCamera_h__
