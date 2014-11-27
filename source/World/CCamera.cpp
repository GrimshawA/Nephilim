#include <Nephilim/World/CCamera.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

CCamera::CCamera()
: up(0.f, 1.f, 0.f)
, eye(0.f, 20.f, 20.f)
, position(0.f, 0.f, 0.f)
, x(0.f)
, y(20.f)
, z(20.f)
, mOrtho(false)
, zNear(1.f)
, zFar(800.f)
, fieldOfView(90.f)
, size(1.f, 1.f)
{
	
}

void CCamera::setSize(float width, float height)
{
	size.x = width;
	size.y = height;
}

/// Returns a ready projection matrix for these configs
mat4 CCamera::getProjection()
{
	if (mOrtho)
	{
		return mat4::ortho(0.f, size.x, 0.f, size.y, 1.f, 4000.f);
	}
	else
	{
		return mat4::perspective(50.f, 1.2f, 1.f, 3000.f);
	}
}

};
NEPHILIM_NS_END
