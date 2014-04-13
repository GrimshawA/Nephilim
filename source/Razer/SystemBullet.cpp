#include <Nephilim/Razer/SystemBullet.h>

#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/BulletDynamics/Character/btKinematicCharacterController.h>
#include <bullet/BulletCollision/CollisionDispatch/btGhostObject.h>
#include <bullet/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include <bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

SystemBullet::SystemBullet()
{

	// add ground plane
	  btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
	  btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
	  btRigidBody::btRigidBodyConstructionInfo
		  groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
	  btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);

	  bulletWorld.m_scene->addRigidBody(groundRigidBody);

}

void SystemBullet::update(float delta)
{
	for(int i = 0; i < 4; i++)
	{
		bulletWorld.step(delta / 4.f);
	}
}

};
NEPHILIM_NS_END