#ifndef NephilimWorldAProjectedWaterComponent_h__
#define NephilimWorldAProjectedWaterComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/Components/ASceneComponent.h>

#include <Nephilim/Graphics/GraphicsDevice.h>

NEPHILIM_NS_BEGIN

/**
	\class AProjectedWaterComponent
	\brief Place a water body in the game world

	This is a very special water technique, usually for big oceans.
	This has absolutely no mesh, the water is rendered with a projected
	grid technique so it has a very particular behavior shape-wise.
	
	The waves itself and graphics can be tweaked tho.
*/
class NEPHILIM_API AProjectedWaterComponent : public ASceneComponent
{
public:
	AProjectedWaterComponent();

	void init();

	void redisplayFunc();

	void render2(GraphicsDevice* mRenderer);

	bool ready;

	mat4 viewMatrix;
	mat4 projMatrix;
	vec3 cameraPosition;

	float mCameraPhi;
	float mCameraTheta;
};

NEPHILIM_NS_END
#endif // NephilimWorldAProjectedWaterComponent_h__
