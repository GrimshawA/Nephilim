#include <Nephilim/BxVehicle.h>
#include <Nephilim/BxScene.h>
#include <Nephilim/MMath.h>
#include <Nephilim/Logger.h>

#include <bullet/btBulletDynamicsCommon.h>

NEPHILIM_NS_BEGIN

BxVehicle::BxVehicle(BxScene& scene)
{	

	float mass = 800;

	btCollisionShape* boxShape = new btBoxShape(btVector3(1.f,0.5f,2.f));

	//btDefaultMotionState* fallMotionState2 = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0, 0, 0)));
	btDefaultMotionState* fallMotionState2 = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0, 3, 0)));

	btScalar mass2 = mass;
	btVector3 fallInertia2(0,0,0);
	boxShape->calculateLocalInertia(mass2,fallInertia2);

	btCompoundShape* compound = new btCompoundShape();
	compound->addChildShape(btTransform(btQuaternion(0,0,0,1),btVector3(0, 0, 0)), boxShape);

	compound->calculateLocalInertia(mass2, fallInertia2);

	btRigidBody::btRigidBodyConstructionInfo chassisCI(mass2,fallMotionState2,compound,fallInertia2);
	chassisCI.m_friction = 5.f;
	m_carChassis = new btRigidBody(chassisCI);

	scene.m_scene->addRigidBody(m_carChassis);

	btCylinderShapeX* m_wheelShape = new btCylinderShapeX(btVector3(0.05,0.2,0.2));

	m_vehicleRayCaster = new btDefaultVehicleRaycaster(scene.m_scene);

	///never deactivate the vehicle
	m_carChassis->setActivationState(DISABLE_DEACTIVATION);

	
	vehicle = new btRaycastVehicle(m_tuning, m_carChassis, m_vehicleRayCaster);
	//vehicle->
	scene.m_scene->addVehicle(vehicle);
	//scene.m_scene->addAction(vehicle);

	//choose coordinate system
	vehicle->setCoordinateSystem(0,1,2);
	//vehicle->updateVehicle(1 / 60.f);
	//vehicle->resetSuspension();

	Log("Vehicle speed: %f", vehicle->getCurrentSpeedKmHour());

	float wheelHeight = 0.f;

	// Wheels
	btVector3 connectionPointCS0(-1,wheelHeight,-1);
	btVector3 connectionPointCS1(1,wheelHeight,-1);
	btVector3 connectionPointCS2(-1,wheelHeight,1);
	btVector3 connectionPointCS3(1,wheelHeight,1);

	btVector3 wheelDirectionCS0(0,-1,0);
	btVector3 wheelAxleCS(-1,0,0);

	vehicle->addWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, 0.6, 0.5, m_tuning, true);
	vehicle->addWheel(connectionPointCS1, wheelDirectionCS0, wheelAxleCS, 0.6, 0.5, m_tuning, true);
	vehicle->addWheel(connectionPointCS2, wheelDirectionCS0, wheelAxleCS, 0.6, 0.5, m_tuning, false);
	vehicle->addWheel(connectionPointCS3, wheelDirectionCS0, wheelAxleCS, 0.6, 0.5, m_tuning, false);

	float	gVehicleSteering = 0.f;
	float	steeringIncrement = 0.04f;
	float	steeringClamp = 0.3f;
	float	wheelRadius = 0.5f;
	float	wheelWidth = 0.4f;
	float	wheelFriction = 1000;//BT_LARGE_FLOAT;
	float	suspensionStiffness = 20.f;
	float	suspensionDamping = 2.3f;
	float	suspensionCompression = 4.4f;
	float	rollInfluence = 0.1f;//1.0f;

	for (int i=0;i<vehicle->getNumWheels();i++)
	{
		btWheelInfo& wheel = vehicle->getWheelInfo(i);
		wheel.m_suspensionStiffness = suspensionStiffness;
		wheel.m_wheelsDampingRelaxation = suspensionDamping;
		wheel.m_wheelsDampingCompression = suspensionCompression;
		wheel.m_frictionSlip = wheelFriction;
		wheel.m_rollInfluence = rollInfluence;
		wheel.m_rotation = Math::pi/4;
	}

	Log("Vehicle created.\nNum Wheels: %d", vehicle->getNumWheels());
}

NEPHILIM_NS_END