#include <Nephilim/3DView.h>
//#include "Nephilim/Math.h"

#include "Nephilim/CGL.h"

#ifdef PARABOLA_ANDROID
#include <Nephilim/RendererGLES.h>
#elif defined PARABOLA_WINDOWS
#include <Windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#endif

PARABOLA_NAMESPACE_BEGIN

/// Apply the camera to openGL
void View3D::apply(){
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45, 480/320, 0.3f, 100000.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(m_eye.x,m_eye.y,m_eye.z, m_center.x, m_center.y, m_center.z, m_up.x, m_up.y, m_up.z);
};

void View3D::forward(float amount)
{
	Vec3f dir = m_center - m_eye;
	dir.normalize();
	m_eye += dir * amount;
	m_center += dir * amount;
}

void View3D::backward(float amount)
{
	Vec3f dir = m_center - m_eye;
	dir.normalize();
	m_eye -= dir * amount;
	m_center += dir * amount;
}

void View3D::strafe(float amount)
{
	/*Vec3f sideways = m_up.cross(m_center - m_eye);
	sideways.normalize();
	sideways *= -amount;
	m_eye += sideways;
	m_center += sideways;*/
}

void View3D::rotateH(float amount)
{
	/*float currAngle = Math::computeAngle(m_eye.x, m_eye.z, m_center.x, m_center.z);
	float dist = Math::distance(m_eye.x, m_eye.z, m_center.x, m_center.z);
	currAngle += amount;
	if(currAngle > Math::pi*2) currAngle -= Math::pi*2;
//	if(currAngle < 0.f) currAngle = Math::pi*2 - currAngle;

	m_center.x = cos(currAngle) * dist;
	m_center.z = sin(currAngle) * dist;*/
}




PARABOLA_NAMESPACE_END