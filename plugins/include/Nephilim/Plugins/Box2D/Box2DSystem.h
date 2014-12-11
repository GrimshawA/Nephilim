#ifndef NephilimPluginBox2DSystem_h__
#define NephilimPluginBox2DSystem_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/World/PhysicsSystem.h>

class b2World;

NEPHILIM_NS_BEGIN

class GraphicsDevice;

/**
	\class Box2DSystem
	\brief Handles the Box2D library as a physics system, simulating our world
*/
class NEPHILIM_API Box2DSystem : public PhysicsSystem
{
public:

	b2World* mSimulation;

public:
	/// Initialize the physics world right away
	Box2DSystem();

	/// Ensure the physics get destroyed
	~Box2DSystem();

	/// Step forward the simulation
	void update(const Time& deltaTime);

	/// Debug draw the shapes
	void debugDraw(GraphicsDevice* graphicsDevice);

	void spawnTestBox(Vector2D position, Vector2D dims);

};

NEPHILIM_NS_END
#endif // NephilimPluginBox2DSystem_h__
