#ifndef NephilimRazerComponentCamera_h__
#define NephilimRazerComponentCamera_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/Matrix.h>
#include <Nephilim/Razer/Component.h>

NEPHILIM_NS_BEGIN
namespace rzr {

/**
	\class CCamera
	\brief 
*/
class NEPHILIM_API CCamera : public Component
{
public:
	CCamera();

	void setSize(float width, float height);

	vec2 size; /// The size of the ortho camera

	vec3 position;
	vec3 eye;
	vec3 up;

	mat4 cameraTransform;

	float x,y,z; // where the camera is
	float center_x, center_y, center_z;

	bool mOrtho; // is it ortho or perspective
	float fieldOfView;
	float zNear;
	float zFar;

	float screenWidth;
	float screenHeight;
};

};
NEPHILIM_NS_END
#endif // NephilimRazerComponentCamera_h__
