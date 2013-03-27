#ifndef PARABOLA_PARTICLEPOINTRENDERER_H
#define PARABOLA_PARTICLEPOINTRENDERER_H

#include "Platform.h"
#include "SPARK.h"

PARABOLA_NAMESPACE_BEGIN

class PARABOLA_API ParticlePointRenderer : public SPK::Renderer, public SPK::PointRenderBehavior{
public:
	static  SPK::Ref<ParticlePointRenderer> create(float screenSize = 1.0f);
};

PARABOLA_NAMESPACE_END
#endif