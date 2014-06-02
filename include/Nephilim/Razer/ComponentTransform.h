#ifndef NephilimRazerComponentTransform_h__
#define NephilimRazerComponentTransform_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Matrix.h>
#include <Nephilim/Quaternion.h>
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
	/// Initialize the transform to the "identity" transform
	/// position(0,0,0), orientation as identity (down the -z axis), and a scale of 1
	ComponentTransform();

	/// Set the position from a vec3
	void setPosition(const vec3& p);

	/// Set the position from a vec2
	void setPosition(const vec2& p);

	/// Set the position from 3 floats
	void setPosition(float px, float py);

	/// Set the position from 3 floats
	void setPosition(float px, float py, float pz);

	/// Get the position of this transform
	vec3 getPosition();

	void rotateByEulerAngles(float x_axis, float y_axis, float z_axis);
	void rotateByAxisAngle(float angle, float x_axis, float y_axis, float z_axis);

	vec3 getForwardVector();
	vec3 getRightVector();

	Quaternion rotation;
	vec3       position;
	vec3       scale;

	mat4 matrix;
};

};
NEPHILIM_NS_END
#endif // NephilimRazerComponentTransform_h__
