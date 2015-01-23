#ifndef NephilimRazerComponentKinesisBody2D_h__
#define NephilimRazerComponentKinesisBody2D_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Vector.h>
#include <Nephilim/World/Component.h>

NEPHILIM_NS_BEGIN

class KxBody;

namespace rzr
{

/**
	\class ComponentKinesisBody2D
	\brief Holds a b2Body* reference in a Box2D world
*/
class NEPHILIM_API ComponentKinesisBody2D : public Component
{
public:
	void setVelocity(float x, float y);

	void applyForceToCenter(float x, float y);

	void setPosition(float x, float y);

	void setPosition(const vec2& p);

	vec2 getPosition();

	void setFixedRotation(bool enable);

	void setRotation(float angle);

	float getRotation();

	KxBody* body;
};

};
NEPHILIM_NS_END

#endif // NephilimRazerComponentTransform2D_h__