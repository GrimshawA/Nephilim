#ifndef NephilimWorldAPointLightComponent_h__
#define NephilimWorldAPointLightComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/Components/ASceneComponent.h>

#include <Nephilim/Foundation/Vector.h>

NEPHILIM_NS_BEGIN

/**
	\class CPointLight
	\brief An individual omni-directional light
*/
class NEPHILIM_API APointLightComponent : public ASceneComponent
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
	APointLightComponent();
};

NEPHILIM_NS_END
#endif // NephilimWorldAPointLightComponent_h__
