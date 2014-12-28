#ifndef NephilimRazerCLight_h__
#define NephilimRazerCLight_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Math/Vectors.h>
#include <Nephilim/World/Component.h>

NEPHILIM_NS_BEGIN

namespace rzr {

/**
	\class CLight
	\brief A light source component

	This light can dynamically become a spotlight, a directional light
	a point light or even an area light.	
*/
class NEPHILIM_API CLight : public Component
{
public:
	enum ELightType
	{
		Point,
		Directional,
		Spot,
		Area
	};

	ELightType type;
};

};
NEPHILIM_NS_END

#endif // NephilimRazerCLight_h__
