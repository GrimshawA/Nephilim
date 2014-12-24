#include <Nephilim/World/CTransform.h>

NEPHILIM_NS_BEGIN

CTransform::CTransform()
: position(0.f, 0.f, 0.f)
, scale(1.f, 1.f, 1.f)
{
}

/// Construct from a position
CTransform::CTransform(vec3 pos)
: position(pos)
, scale(1.f, 1.f, 1.f)
{

}

/// Sets the position from a vec3
void CTransform::setPosition(const vec3& p)
{
	position = p;
}

/// Set the position from a vec2
void CTransform::setPosition(const vec2& p)
{
	position.x = p.x;
	position.y = p.y;
}

/// Set the position from 3 floats
void CTransform::setPosition(float px, float py)
{
	position.x = px;
	position.y = py;
}

/// Makes this transform orient itself to the target
void CTransform::setLookAt(Vector3D target)
{
	Vector3D D = target - position;
	D.normalize();

	Vector3D U(0.f, 1.f, 0.f);

	Vector3D S = D.cross(U);
	S.normalize();

	Vector3D Un = S.cross(D);
	Un.normalize();

	mat4 rmat = mat4::identity;

	rmat[0] = D.x;
	rmat[1] = D.y;
	rmat[2] = D.z;

	rmat[4] = Un.x;
	rmat[5] = Un.y;
	rmat[6] = Un.z;

	rmat[8] = S.x;
	rmat[9] = S.y;
	rmat[10] = S.z;

	rmat[0] = S.x;
	rmat[1] = Un.x;
	rmat[2] = D.x;

	rmat[4] = S.y;
	rmat[5] = Un.y;
	rmat[6] = D.y;

	rmat[8] = S.z;
	rmat[9] = Un.z;
	rmat[10] = D.z;

	rotation = Quaternion::fromMatrix(rmat);

	mat4 m = mat4::lookAt(Vector3D(0.f, 0.f, 0.f), D, U).inverse();
	rotation = Quaternion::fromMatrix(m);
}

/// Set the position from 3 floats
void CTransform::setPosition(float px, float py, float pz)
{
	position.x = px;
	position.y = py;
	position.z = pz;
}

/// Get the position of this transform
vec3 CTransform::getPosition()
{
	return position;
}

mat4 CTransform::getMatrix()
{
	//matrix = rotation.toMatrix() * mat4::translate(position.x, position.y, position.z) * mat4::scale(scale.x, scale.y, scale.z);
	matrix = mat4::translate(position.x, position.y, position.z) * mat4::scale(scale.x, scale.y, scale.z) * rotation.toMatrix();
	return matrix;
}

void CTransform::rotateByEulerAngles(float x_axis, float y_axis, float z_axis)
{
	rotation.rotateEulerAngles(x_axis, y_axis, z_axis);
}

void CTransform::rotateByAxisAngle(float angle, float x_axis, float y_axis, float z_axis)
{
	rotation.rotateAxisAngle(angle, x_axis, y_axis, z_axis);
}

vec3 CTransform::getForwardVector()
{
	rotation.normalize();

	vec4 v(0.f, 0.f, -1.f, 0.f);

	mat4 rm = rotation.toMatrix();
	//rm.invert();

	v = rm * v;
	v.normalize();

	return v.xyz();
}

vec3 CTransform::getRightVector()
{
	rotation.normalize();

	vec4 v(1.f, 0.f, 0.f, 0.f);

	mat4 rm = rotation.toMatrix()/* * mat4::scale(1,1,1)*/;

	v = rm * v;
	v.normalize();

	return v.xyz();
}

NEPHILIM_NS_END