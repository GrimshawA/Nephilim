#include <Nephilim/Razer/ComponentVehicle.h>
#include <Nephilim/Logger.h>

#ifdef NEPHILIM_DESKTOP
#include <Nephilim/MeshImport/AssimpConverter.h>
#endif

NEPHILIM_NS_BEGIN
namespace rzr
{

ComponentVehicle::ComponentVehicle()
: ready(false)
{
}

void ComponentVehicle::prepareModels()
{
	#ifdef NEPHILIM_DESKTOP
	// use assimp to load a car and use that to render later
	AssimpImport ai;
	if(ai.load("car.obj"))
	{
		Log("Vehicle mesh being loaded");

		AssimpGeometry(testModel, ai);

		testModelMatrix = mat4::translate(-2.4, -1, 0) * mat4::scale(0.005f, 0.005f, 0.005f);
	}

	testTexture.loadFromFile("cart.jpg");
	testTexture.setRepeated(true);
#endif
}

void ComponentVehicle::applyEngineForce(float force, int wheelIndex)
{
	vehicle->vehicle->applyEngineForce(force, wheelIndex);
}



}
NEPHILIM_NS_END