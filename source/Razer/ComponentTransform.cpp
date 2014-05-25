#include <Nephilim/Razer/ComponentTransform.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

void ComponentTransform::rotateAxisAngle(float x_axis, float y_axis, float z_axis)
{
	rotation.rotateEulerAngles(x_axis, y_axis, z_axis);
}

vec3 ComponentTransform::getForwardVector()
{
	rotation.normalize();

	vec4 v(0.f, 0.f, -1.f, 0.f);

	mat4 rm = rotation.toMatrix();
	rm.invert();

	v = rm * v;
	v.normalize();

	return v.xyz();
}

vec3 ComponentTransform::getRightVector()
{
	rotation.normalize();

	vec4 v(1.f, 0.f, 0.f, 0.f);

	mat4 rm = rotation.toMatrix()/* * mat4::scale(1,1,1)*/;
	rm.invert();

	v = rm * v;
	v.normalize();

	return v.xyz();
}

};
NEPHILIM_NS_END