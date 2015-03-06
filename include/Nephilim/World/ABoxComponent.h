#ifndef NephilimWorld_ABoxComponent_h__
#define NephilimWorld_ABoxComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/ASceneComponent.h>
#include <Nephilim/World/RigidBody.h>

NEPHILIM_NS_BEGIN

/**
	\class ABoxComponent
	\brief Places a physical box into the world
*/
class NEPHILIM_API ABoxComponent : public ASceneComponent
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
	ABoxComponent();

	/// Construct the collider from a dynamic flag and dimensions
	ABoxComponent(bool isDynamic, Vector3D dims);
};

NEPHILIM_NS_END
#endif // NephilimWorld_ABoxComponent_h__
