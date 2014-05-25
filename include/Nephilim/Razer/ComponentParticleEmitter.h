#ifndef NephilimRazerComponentParticleEmitter_h__
#define NephilimRazerComponentParticleEmitter_h__

#include <Nephilim/Platform.h>
#include <Nephilim/RectangleShape.h>
#include <Nephilim/Razer/Component.h>

NEPHILIM_NS_BEGIN

namespace rzr
{
/**
	\class 
	\brief 
*/
class NEPHILIM_API ComponentParticleEmitter : public Component
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

};
NEPHILIM_NS_END
#endif // NephilimRazerComponentParticleEmitter_h__