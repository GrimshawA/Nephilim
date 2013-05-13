#ifndef NephilimBxVehicle_h__
#define NephilimBxVehicle_h__

#include "Platform.h"
#include <BulletDynamics/Vehicle/btRaycastVehicle.h>

NEPHILIM_NS_BEGIN

class BxScene;

class NEPHILIM_API BxVehicle
{
public:

	BxVehicle(BxScene& scene);

	void update()
	{
		for (int i=0;i<vehicle->getNumWheels();i++)
		{
			//synchronize the wheels with the (interpolated) chassis worldtransform
			vehicle->updateWheelTransform(i,true);
		}
	}

	btDefaultVehicleRaycaster* m_vehicleRayCaster;
	btRigidBody* m_carChassis;
	btRaycastVehicle::btVehicleTuning m_tuning;
	btRaycastVehicle* vehicle;
};

NEPHILIM_NS_END
#endif // NephilimBxVehicle_h__
