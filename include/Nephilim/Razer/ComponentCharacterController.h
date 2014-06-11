#ifndef NephilimRazerComponentCharacterController_h__
#define NephilimRazerComponentCharacterController_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/Matrix.h>
#include <Nephilim/Razer/Component.h>

#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/BulletDynamics/Character/btKinematicCharacterController.h>
#include <bullet/BulletCollision/CollisionDispatch/btGhostObject.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

/**
	\class ComponentCharacterController
	\brief 
*/
class NEPHILIM_API ComponentCharacterController : public Component
{
public:
	ComponentCharacterController();

	void setVelocity(const vec3& v);

	vec3 getPosition();

	btKinematicCharacterController* m_character;
	btGhostObject *m_ghostObject;
};

};
NEPHILIM_NS_END
#endif // NephilimRazerComponentCharacterController_h__