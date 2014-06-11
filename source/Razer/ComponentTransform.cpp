#include <Nephilim/Razer/ComponentTransform.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

ComponentTransform::ComponentTransform()
: position(0.f, 0.f, 0.f)
, scale(1.f, 1.f, 1.f)
{
}

/// Sets the position from a vec3
void ComponentTransform::setPosition(const vec3& p)
{
	position = p;
}

/// Set the position from a vec2
void ComponentTransform::setPosition(const vec2& p)
{
	position.x = p.x;
	position.y = p.y;
}

/// Set the position from 3 floats
void ComponentTransform::setPosition(float px, float py)
{
	position.x = px;
	position.y = py;
}

/// Set the position from 3 floats
void ComponentTransform::setPosition(float px, float py, float pz)
{
	position.x = px;
	position.y = py;
	position.z = pz;
}

/// Get the position of this transform
vec3 ComponentTransform::getPosition()
{
	return position;
}

mat4 ComponentTransform::getMatrix()
{
	matrix = rotation.toMatrix() * mat4::translate(position.x, position.y, position.z) * mat4::scale(scale.x, scale.y, scale.z);
	return matrix;
}

void ComponentTransform::rotateByEulerAngles(float x_axis, float y_axis, float z_axis)
{
	rotation.rotateEulerAngles(x_axis, y_axis, z_axis);
}

void ComponentTransform::rotateByAxisAngle(float angle, float x_axis, float y_axis, float z_axis)
{
	rotation.rotateAxisAngle(angle, x_axis, y_axis, z_axis);
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