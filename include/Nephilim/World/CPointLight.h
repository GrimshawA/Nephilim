#ifndef NephilimWorldPointLight_h__
#define NephilimWorldPointLight_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Vector.h>
#include <Nephilim/World/Component.h>

NEPHILIM_NS_BEGIN

/**
	\class CPointLight
	\brief An individual omni-directional light
*/
class NEPHILIM_API CPointLight : public Component
{
public:
	
	/// Does this light cast shadows at all?
	bool mCastShadows;

	/// How far can this light reach before fading out
	float mAttenuationRadius;

	/// The color this light emits
	Vector3D mLightColor;

public:

	/// Default construction of this light
	CPointLight();
};

NEPHILIM_NS_END
#endif // NephilimWorldPointLight_h__
