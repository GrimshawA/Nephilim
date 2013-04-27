#ifndef ParticleSystem_h__
#define ParticleSystem_h__

#include "Platform.h"
#include "Drawable.h"
#include "Sprite.h"
#include "Texture.h"

NEPHILIM_NS_BEGIN

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

	Texture tex;
	std::vector<Sprite> m_particles;
};

NEPHILIM_NS_END
#endif // ParticleSystem_h__
