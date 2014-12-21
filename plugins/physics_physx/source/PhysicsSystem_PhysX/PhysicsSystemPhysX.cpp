#include "PhysicsSystemPhysX.h"

#include <Nephilim/Logger.h>

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
}

String PhysicsSystemPhysX::getName()
{
	return "PhysX";
}

void PhysicsSystemPhysX::update(const Time& deltaTime)
{
	Log("Hey Dude");

	mScene->simulate(deltaTime.asSeconds());

	if (aSphereActor)
	{
		if (mScene->fetchResults())
		{
			Log("SIMULATING SPHERE at %f %f %f", aSphereActor->getGlobalPose().p.x, aSphereActor->getGlobalPose().p.y, aSphereActor->getGlobalPose().p.z);
		}
	}
}