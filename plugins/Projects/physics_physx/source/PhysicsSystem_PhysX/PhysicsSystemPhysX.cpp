#include <Nephilim/World/World.h>
#include <Nephilim/World/CColliderBox.h>
#include <Nephilim/World/ACharacterComponent.h>

#include "PhysicsSystemPhysX.h"

#include <Nephilim/Foundation/Logging.h>

/// PhysX Stuff
#include <PxPhysicsAPI.h>
#include <extensions/PxDefaultSimulationFilterShader.h>
using namespace physx;

PxRigidDynamic* aSphereActor = NULL;

PhysicsSystemPhysX::PhysicsSystemPhysX()
: PhysicsSystem()
{
	Log("HELLO PHYSX");

	static PxDefaultErrorCallback gDefaultErrorCallback;
	static PxDefaultAllocator gDefaultAllocatorCallback;

	PxFoundation* mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
	if (!mFoundation)
		Log("PxCreateFoundation failed!");

	PxProfileZoneManager* mProfileZoneManager = &PxProfileZoneManager::createProfileZoneManager(mFoundation);
	if (!mProfileZoneManager)
		Log("PxProfileZoneManager::createProfileZoneManager failed!");

	bool recordMemoryAllocations = true;
	mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation,
		PxTolerancesScale(), recordMemoryAllocations, mProfileZoneManager);
	if (!mPhysics)
		Log("PxCreatePhysics failed!");

	if (!PxInitExtensions(*mPhysics))
		Log("PxInitExtensions failed!");

	//	static PxDefaultSimulationFilterShader gDefaultFilterShader;
	//static PxFilterFlags gDefaultFilterShader = 

	PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	sceneDesc.gravity = PxVec3(0.0f, -19.81f, 0.0f);
	//sceneDesc.
	//customizeSceneDesc(sceneDesc);

	if (!sceneDesc.cpuDispatcher)
	{
		PxDefaultCpuDispatcher*  mCpuDispatcher = PxDefaultCpuDispatcherCreate(1);
		if (!mCpuDispatcher)
			Log("PxDefaultCpuDispatcherCreate failed!");
		sceneDesc.cpuDispatcher = mCpuDispatcher;
	}
	if (!sceneDesc.filterShader)
		sceneDesc.filterShader = PxDefaultSimulationFilterShader;

	/*
	#ifdef PX_WINDOWS
	if(!sceneDesc.gpuDispatcher && mCudaContextManager)
	{
	sceneDesc.gpuDispatcher = mCudaContextManager->getGpuDispatcher();
	}
	#endif*/

	mScene = mPhysics->createScene(sceneDesc);
	if (!mScene)
		Log("createScene failed!");


	PxMaterial* mMaterial;

	mMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.1f);    //static friction, dynamic friction, restitution
	if (!mMaterial)
		Log("createMaterial failed!");

	aSphereActor = mPhysics->createRigidDynamic(PxTransform(0, 30, 0));
	PxShape* aSphereShape = aSphereActor->createShape(PxSphereGeometry(1), *mMaterial);
	PxRigidBodyExt::updateMassAndInertia(*aSphereActor, 2);

	mScene->addActor(*aSphereActor);
	aSphereActor->setLinearVelocity(PxVec3(1, 1, 1));

	PxRigidStatic* groundPlaneActor = mPhysics->createRigidStatic(PxTransform(0.f, -10.f, 0.f));
	PxShape* groundShape = groundPlaneActor->createShape(PxBoxGeometry(150.f, 5.f, 150.f), *mMaterial);
	mScene->addActor(*groundPlaneActor);
	 
	manager = PxCreateControllerManager(*mScene);
}

String PhysicsSystemPhysX::getName()
{
	return "PhysX";
}

void PhysicsSystemPhysX::update(const Time& deltaTime)
{	
	// Step the simulation forward
	mScene->simulate(deltaTime.seconds());

	if (mScene->fetchResults())
	{

		// Now let's push back the transforms into the World
		ComponentManager* colliderBoxManager = getWorld()->getComponentManager<CColliderBox>();
		ComponentManager* transformManager = getWorld()->getComponentManager<CTransform>();
		for (std::size_t i = 0; i < colliderBoxManager->size(); ++i)
		{
			Entity E = colliderBoxManager->getInstanceEntity(i);
			CColliderBox* box = (CColliderBox*)colliderBoxManager->getInstance(i);
			CTransform* transform = (CTransform*)transformManager->getComponentFromEntity(E);

			// Create
			if (box->userData == nullptr)
			{
				PxMaterial* boxMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.1f);

				PxRigidDynamic* boxActor = mPhysics->createRigidDynamic(PxTransform(transform->position.x, transform->position.y, transform->position.z));
				boxActor->createShape(PxBoxGeometry(10.f, 10.f, 10.f), *boxMaterial);
				PxRigidBodyExt::updateMassAndInertia(*boxActor, 30);
				//boxActor->setLinearVelocity(PxVec3(0, -50, 0));

				mScene->addActor(*boxActor);
				box->userData = boxActor;
			}
			// Update
			else
			{
				PxRigidDynamic* boxActor = (PxRigidDynamic*)box->userData;
				PxTransform pxTransform = boxActor->getGlobalPose();

				transform->position.x = pxTransform.p.x;
				transform->position.y = pxTransform.p.y;
				transform->position.z = pxTransform.p.z;

				transform->rotation.x = pxTransform.q.x;
				transform->rotation.y = pxTransform.q.y;
				transform->rotation.z = pxTransform.q.z;
				transform->rotation.w = pxTransform.q.w;
			}
		}

		syncActors();
	}
}

/// Let's check if actors are okay
void PhysicsSystemPhysX::syncActors()
{
	for (std::size_t i = 0; i < mWorld->actors.size(); ++i)
	{
		Actor* actor = mWorld->actors[i];

		for (std::size_t j = 0; j < actor->components.size(); ++j)
		{
			ACharacterComponent* chr = dynamic_cast<ACharacterComponent*>(actor->components[j]);
			if (chr)
			{
				// We have a character controller in this actor, needs to be handled
				if (chr->userData)
				{
					PxController* cc = (PxController*)chr->userData;
					

					chr->t.position.x = cc->getPosition().x;
					chr->t.position.y = cc->getPosition().y;
					chr->t.position.z = cc->getPosition().z;

					//Log("Updated actor");
				}
				else
				{
					PxMaterial* mat = mPhysics->createMaterial(0.1, 0.1, 0.1);
 					PxCapsuleControllerDesc* desc = new PxCapsuleControllerDesc;
					desc->height = 5;
					desc->radius = 5;
					desc->position = PxExtendedVec3(0, 0, 0);
					desc->material = mat;
					Log("BOX VALID: %d", desc->isValid());

					PxController* c = manager->createController(*desc);
					if (!c)
					{
						Log("Failed to instance a controller");
					}

					if (c)
					{	
						
						chr->userData = c;
						chr->moving.connect(sigc::mem_fun(this, &PhysicsSystemPhysX::TestCharacterMove));
						Log("PhysX validated an actor's character controller");
					}
				}
			}
		}
	}
}

void PhysicsSystemPhysX::TestCharacterMove(Vector3D displacement, Actor* a)
{
	ACharacterComponent* chr = dynamic_cast<ACharacterComponent*>(a->getRootComponent());
	if (chr)
	{
		if (chr->userData)
		{
			PxController* cc = (PxController*)chr->userData;
			PxControllerFilters filters;
			cc->move(PxVec3(displacement.x, displacement.y, displacement.z), 0.01f, 1.f / 60.f, filters);

			//Log("Moving..");
		}
	}
}