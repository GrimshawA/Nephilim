#include <Nephilim/BxScene.h>

#include <algorithm>

#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/BulletDynamics/Character/btKinematicCharacterController.h>
#include <bullet/BulletCollision/CollisionDispatch/btGhostObject.h>

NEPHILIM_NS_BEGIN

/// Initializes a dynamics world by default
BxScene::BxScene()
: m_scene(NULL)
{
	// Default broadphase
	btVector3 worldMin(-1000,-1000,-1000);
	btVector3 worldMax(1000,1000,1000);
	btAxisSweep3* sweepBP = new btAxisSweep3(worldMin,worldMax);
	m_bp = sweepBP;
	// Default dispatcher
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	// Default solver
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	// Start scene
	m_scene = new btDiscreteDynamicsWorld(dispatcher,sweepBP,solver,collisionConfiguration);

	// Default gravity
	m_scene->setGravity(btVector3(0,-8,0));
}

/// Safely destructs the scene
BxScene::~BxScene()
{
	delete m_scene;
}

/// Add a body to the world
void BxScene::addBody(BxBody* body)
{
	static_cast<btDiscreteDynamicsWorld*>(m_scene)->addRigidBody(static_cast<btRigidBody*>(body->m_body));
	m_bodies.push_back(body);
}

/// Remove the body from the world
void BxScene::removeBody(BxBody* body)
{
	static_cast<btDiscreteDynamicsWorld*>(m_scene)->removeRigidBody(static_cast<btRigidBody*>(body->m_body));
	m_bodies.erase(std::find(m_bodies.begin(), m_bodies.end(), body));
	delete body;
}

/// Step the simulation
void BxScene::step(float deltaTime)
{
	m_scene->stepSimulation(deltaTime);
}

NEPHILIM_NS_END