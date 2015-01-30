#ifndef NephilimWorldAParticleEmitterComponent_h__
#define NephilimWorldAParticleEmitterComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/Components/ASceneComponent.h>

#include <Nephilim/Graphics/RectangleShape.h>

NEPHILIM_NS_BEGIN

/**
	\class AParticleEmitterComponent
	\brief Places a particle emitter in the world
*/
class NEPHILIM_API AParticleEmitterComponent : public ASceneComponent
{
public:

	class Particle
	{
	public:
		RectangleShape mSprite;
		vec3 velocity;
		float angularVelocity;
		float lifetime;
		vec4 color;
	};

	vec2 tex_pos;
	vec2 tex_size;

	std::vector<Particle> particles;
};

NEPHILIM_NS_END
#endif // NephilimWorldAParticleEmitterComponent_h__