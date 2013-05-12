#ifndef NephilimBxScene_h__
#define NephilimBxScene_h__

#include "Platform.h"
#include "BxBody.h"

#include <vector>

class btDynamicsWorld;
class btAxisSweep3;

NEPHILIM_NS_BEGIN

/**
	\ingroup BulletWrapper
	\class BxScene
	\brief Wraps a Bullet world simulation
*/
class NEPHILIM_API BxScene
{
public:
	/// Initializes a dynamics world by default
	BxScene();

	/// Safely destructs the scene
	~BxScene();

	/// Add a body to the world
	void addBody(BxBody* body);

	/// Remove the body from the world
	void removeBody(BxBody* body);

	/// Step the simulation
	void step(float deltaTime);

/*private:*/
	btDynamicsWorld* m_scene;
	btAxisSweep3* m_bp;

	std::vector<BxBody*> m_bodies;
};

NEPHILIM_NS_END
#endif // NephilimBxScene_h__
