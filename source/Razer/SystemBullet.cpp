#include <Nephilim/Razer/SystemBullet.h>
#include <Nephilim/Razer/Scene.h>
#include <Nephilim/Razer/Entity.h>
#include <Nephilim/Razer/Entity.inl>
#include <Nephilim/Razer/ComponentCharacterController.h>
#include <Nephilim/Razer/ComponentTransform.h>
#include <Nephilim/Razer/ComponentTerrain.h>
#include <Nephilim/Razer/ComponentTerrainCollider.h>
#include <Nephilim/Razer/ComponentVehicle.h>

#include <Nephilim/Logger.h>

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
	 /* btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
	  btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
	  btRigidBody::btRigidBodyConstructionInfo
		  groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
	  btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	  
	  bulletWorld.m_scene->addRigidBody(groundRigidBody);*/
}


static const float GRID_SIZE = 1.0f;
static const float HEIGHT_FACTOR = 0.1f;
static const float TEXTURE_INCREMENT = 0.2f;
#include <bullet/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include <bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>

void SystemBullet::update(const Time& deltaTime)
{
	float delta = deltaTime.asSeconds();


	for(std::size_t i = 0; i < mScene->mEntities.size(); ++i)
	{
		Entity entity = mScene->getEntityByIndex(i);
		if(entity.hasComponent<ComponentVehicle>())
		{
			ComponentVehicle& vehicle = entity.getComponent<ComponentVehicle>();
			if(!vehicle.ready)
			{
				vehicle.vehicle = new BxVehicle(bulletWorld);

				vehicle.vehicleChassis.addBox(2,1,4);
				vehicle.vehicleChassis.setAllColors(Color::White);

				vehicle.vehicleWheel.addBox(1,1,1);
				vehicle.vehicleWheel.setAllColors(Color::White);

				vehicle.prepareModels();

				Log("VEHICLE SPAWNED");

				vehicle.ready = true;
			}
		}
		if(entity.hasComponent<ComponentCharacterController>())
		{
			ComponentCharacterController& cc = entity.getComponent<ComponentCharacterController>();

			if(cc.m_character == NULL)
			{
				/// Add character capsule
				btTransform startTransform;
				startTransform.setIdentity ();
				startTransform.setOrigin (btVector3(0,35,0));

				cc.m_ghostObject = new btPairCachingGhostObject();
				cc.m_ghostObject->setWorldTransform(startTransform);
				bulletWorld.m_bp->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
				btScalar characterHeight=1.75;
				btScalar characterWidth =1.75;
				btConvexShape* capsule = new btCapsuleShape(characterWidth,characterHeight);
				cc.m_ghostObject->setCollisionShape (capsule);
				cc.m_ghostObject->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);

				btScalar stepHeight = btScalar(0.5f);
				cc.m_character = new btKinematicCharacterController ((btPairCachingGhostObject*)cc.m_ghostObject,capsule,stepHeight);

				bulletWorld.m_scene->addCollisionObject(cc.m_ghostObject,btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter|btBroadphaseProxy::AllFilter);

				bulletWorld.m_scene->addAction(cc.m_character);

				bulletWorld.m_scene->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(cc.m_ghostObject->getBroadphaseHandle(),bulletWorld.m_scene->getDispatcher());
				bulletWorld.m_scene->getDispatchInfo().m_allowedCcdPenetration=0.00001f;
			}
			
		}
		if(entity.hasComponent<ComponentTerrainCollider>() && entity.hasComponent<ComponentTerrain>())
		{
			ComponentTerrainCollider& terrainCollider =  entity.getComponent<ComponentTerrainCollider>();
			ComponentTerrain& terrain =  entity.getComponent<ComponentTerrain>();

			if(!terrainCollider.ready)
			{
				btHeightfieldTerrainShape* terrainShape = new btHeightfieldTerrainShape(terrain.heightmap.getSize().x,terrain.heightmap.getSize().y, terrain.heightmapRaw, HEIGHT_FACTOR, 0, 255*HEIGHT_FACTOR, 1, PHY_UCHAR, false);
				btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
				btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));

				btRigidBody::btRigidBodyConstructionInfo
					groundRigidBodyCI(0,groundMotionState,terrainShape,btVector3(0,0,0));

				groundRigidBodyCI.m_friction = 2.f;

				btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
				bulletWorld.m_scene->addRigidBody(groundRigidBody);
				terrainShape->setUseDiamondSubdivision(true);

				Log("Added the terrain collider");

				terrainCollider.ready = true;
			}
		}
	}

	//for(int i = 0; i < 4; i++)
	//{
		bulletWorld.step(delta);
	//}

	for(std::size_t i = 0; i < mScene->mEntities.size(); ++i)
	{
		Entity entity = mScene->getEntityByIndex(i);
		if(entity.hasComponent<ComponentCharacterController>())
		{
			ComponentCharacterController& cc = entity.getComponent<ComponentCharacterController>();
			ComponentTransform& transform = entity.getComponent<ComponentTransform>();

			vec3 ccPosition(cc.m_ghostObject->getWorldTransform().getOrigin().getX(), cc.m_ghostObject->getWorldTransform().getOrigin().getY(), cc.m_ghostObject->getWorldTransform().getOrigin().getZ());

			btQuaternion quat = cc.m_ghostObject->getWorldTransform().getRotation();

			transform.position = ccPosition;
		//	transform.rotation = Quaternion(quat.getX(),quat.getY(),quat.getZ(),quat.getW() );


			//Log("Transform updated");
		}
	}
}

};
NEPHILIM_NS_END