#ifndef NephilimRazerComponentSpotLight_h__
#define NephilimRazerComponentSpotLight_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/World/Component.h>

NEPHILIM_NS_BEGIN

namespace rzr {

/**
	\class CDirectionalLight
	\brief Allows to add directional lights to the scene (sun)

	This is almost always used to simulate the sunlight,
	since the light comes in parallel, affecting everything
	which implies a really far and really big light source.
*/
class NEPHILIM_API CSpotLight : public Component
{
public:
	
};

};
NEPHILIM_NS_END
#endif // NephilimRazerComponentSpotLight_h__
