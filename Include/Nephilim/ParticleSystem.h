#ifndef ParticleSystem_h__
#define ParticleSystem_h__

#include "Platform.h"
#include "Drawable.h"
#include "Sprite.h"
#include "Texture.h"

NEPHILIM_NS_BEGIN
class ParticleEmitter
{
public:


	vec3 m_position;
};

class Particle
{
public:

	vec3 position;
	vec3 velocity;

	Sprite s;
};

/**
	\ingroup Graphics
	\class ParticleSystem
	\brief Highly configurable particle effects
*/
class NEPHILIM_API ParticleSystem : public Drawable
{
public:
	/// Construct a empty particle system
	ParticleSystem();

	/// Df
	void create();

	/// Update the system
	void update(float deltaTime);

	/// Draw the particle system
	virtual void onDraw(Renderer* renderer);

	Texture *tex;
	std::vector<Particle> m_particles;
	int counter;

	vec3 position;
	int tank;
};



NEPHILIM_NS_END
#endif // ParticleSystem_h__
