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

	/// Size of our box
	Vector3D size;

	bool _isDynamic;

public:

	/// By default, a collider is dynamic and has size 10
	CColliderBox();

	/// Construct the collider from a dynamic flag and dimensions
	CColliderBox(bool isDynamic, Vector3D dims);
};

NEPHILIM_NS_END
#endif // NephilimRazerComponentBoxCollider_h__
