#include <Nephilim/World/CPointLight.h>

NEPHILIM_NS_BEGIN

/// Default construction of this light
CPointLight::CPointLight()
: mCastShadows(true)
, mAttenuationRadius(100.f)
, mLightColor(1.f, 1.f, 1.f)
{

}

NEPHILIM_NS_END