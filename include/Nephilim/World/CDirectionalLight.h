#ifndef NephilimRazerComponentDirectionalLight_h__
#define NephilimRazerComponentDirectionalLight_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Math/Vectors.h>
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
class NEPHILIM_API CDirectionalLight : public Component
{
public:
	/// The direction this light faces
	vec3 direction;
};

};
NEPHILIM_NS_END
#endif // NephilimRazerComponentDirectionalLight_h__