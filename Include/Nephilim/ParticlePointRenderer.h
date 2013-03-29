#ifndef PARABOLA_PARTICLEPOINTRENDERER_H
#define PARABOLA_PARTICLEPOINTRENDERER_H

#include "Platform.h"
#include "SPARK.h"

NEPHILIM_NS_BEGIN

class NEPHILIM_API ParticlePointRenderer : public SPK::Renderer, public SPK::PointRenderBehavior{
public:
	static  SPK::Ref<ParticlePointRenderer> create(float screenSize = 1.0f);
};

NEPHILIM_NS_END
#endif