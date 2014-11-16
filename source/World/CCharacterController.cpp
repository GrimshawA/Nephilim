#include <Nephilim/Razer/CCharacterController.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

CCharacterController::CCharacterController()
: m_character(NULL)
, m_ghostObject(NULL)
{
}

void CCharacterController::setVelocity(const vec3& v)
{
	if(m_character)
	{
		m_character->setWalkDirection(btVector3(v.x,v.y,v.z));
	}
}

vec3 CCharacterController::getPosition()
{
	vec3 p(0.f, 0.f, 0.f);
	if(m_character)
	{
		btTransform t = m_ghostObject->getWorldTransform();
		p.x = t.getOrigin().getX();
		p.y = t.getOrigin().getY();
		p.z = t.getOrigin().getZ();
	}
	return p;
}


};
NEPHILIM_NS_END
