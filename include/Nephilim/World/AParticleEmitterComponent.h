#ifndef NephilimWorld_AParticleEmitterComponent_h__
#define NephilimWorld_AParticleEmitterComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/ASceneComponent.h>

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
		Vector3D position;

		RectangleShape mSprite;
		vec3 velocity;
		float angularVelocity;
		float lifetime;
		vec4 color;
	};

	vec2 tex_pos;
	vec2 tex_size;

	std::vector<Particle> particles;

public:

	/// Update the particles
	void update(float deltaTime);
};

NEPHILIM_NS_END
#endif // NephilimWorld_AParticleEmitterComponent_h__