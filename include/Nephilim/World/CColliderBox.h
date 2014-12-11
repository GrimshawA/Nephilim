#ifndef NephilimRazerComponentBoxCollider_h__
#define NephilimRazerComponentBoxCollider_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/Component.h>
#include <Nephilim/World/RigidBody.h>

NEPHILIM_NS_BEGIN

/**
	\class CColliderBox
	\brief Adds a solid box to the world

	Using this to debug physics behaviors for now
*/
class NEPHILIM_API CColliderBox : public Component
{
public:
	void* userData = nullptr;

	/// For now hold a rigidBody pointer here
	RigidBody* rigidBody = nullptr;
};

NEPHILIM_NS_END
#endif // NephilimRazerComponentBoxCollider_h__
