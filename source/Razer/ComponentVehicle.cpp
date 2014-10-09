#include <Nephilim/Razer/ComponentVehicle.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

ComponentVehicle::ComponentVehicle()
: ready(false)
{
}

void ComponentVehicle::prepareModels()
{
	
}

void ComponentVehicle::applyEngineForce(float force, int wheelIndex)
{
	vehicle->vehicle->applyEngineForce(force, wheelIndex);
}



}
NEPHILIM_NS_END