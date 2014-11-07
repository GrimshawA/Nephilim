#ifndef NephilimRazerComponentVehicle_h__
#define NephilimRazerComponentVehicle_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Razer/Component.h>
#include <Nephilim/BxVehicle.h>
#include <Nephilim/Graphics/GLTexture.h>
#include <Nephilim/Geometry.h>

NEPHILIM_NS_BEGIN
namespace rzr {

/**
	\class ComponentVehicle
	\brief 
*/
class NEPHILIM_API ComponentVehicle : public Component
{
public:
	ComponentVehicle();

	void applyEngineForce(float force, int wheelIndex);

	GeometryData vehicleChassis;
	GeometryData vehicleWheel;

	void prepareModels();

	Texture testTexture;
	GeometryData testModel;
	mat4 testModelMatrix;

	BxVehicle* vehicle;

	bool ready;
};

};
NEPHILIM_NS_END
#endif // NephilimRazerComponentVehicle_h__
