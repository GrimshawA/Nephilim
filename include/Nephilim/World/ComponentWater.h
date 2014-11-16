#ifndef NephilimComponentWater_h__
#define NephilimComponentWater_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/World/Component.h>

NEPHILIM_NS_BEGIN

namespace rzr {

/**
	\class ComponentWater
	\brief 
*/
class NEPHILIM_API ComponentWater : public Component
{
public:
	ComponentWater();

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

};
NEPHILIM_NS_END
#endif // NephilimComponentWater_h__
