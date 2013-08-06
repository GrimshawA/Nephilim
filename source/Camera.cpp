#include <Nephilim/Camera.h>
#include <Nephilim/MMath.h>

NEPHILIM_NS_BEGIN

FPSCamera::FPSCamera()
{
	m_xAngle = math::pi / 4;
	m_yAngle = 0;
}

void FPSCamera::rotate(float x, float y)
{
	m_xAngle += x;
	m_yAngle += y;

	if(m_yAngle > math::pi/2) m_yAngle = math::pi/2;
	if(m_yAngle < -math::pi/2) m_yAngle = -math::pi/2;
}

vec3 FPSCamera::getPosition()
{
	return m_position;
}

void FPSCamera::setPosition(vec3 position)
{
	m_position = position;
}

vec3 FPSCamera::getDirection()
{
	return directionFromAngles(m_xAngle, m_yAngle);
}

mat4 FPSCamera::getMatrix()
{
	return mat4::rotatex(m_yAngle) * mat4::rotatey(m_xAngle) * mat4::translate(-m_position.x,-m_position.y,-m_position.z);
}

NEPHILIM_NS_END