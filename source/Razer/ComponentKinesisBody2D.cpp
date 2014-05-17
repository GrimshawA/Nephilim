#include <Nephilim/Razer/ComponentKinesisBody2D.h>
#include <Nephilim/KxBody.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

void ComponentKinesisBody2D::setVelocity(float x, float y)
{
	body->setVelocity(vec2(x,y));
}

void ComponentKinesisBody2D::applyForceToCenter(float x, float y)
{
	body->m_body->ApplyForceToCenter(b2Vec2(x,y));
}

vec2 ComponentKinesisBody2D::getPosition()
{
	assert(body != NULL);
	return body->getPosition();
}

void ComponentKinesisBody2D::setPosition(float x, float y)
{
	assert(body != NULL);
	body->setPosition(vec2(x,y));
	Log("Setting Position to %f %f", x,y);
}

void ComponentKinesisBody2D::setPosition(const vec2& p)
{
	assert(body != NULL);
	body->setPosition(p);
}

void ComponentKinesisBody2D::setFixedRotation(bool enable)
{
	body->setFixedRotation(enable);
}

void ComponentKinesisBody2D::setRotation(float angle)
{
	body->m_body->SetTransform(body->m_body->GetPosition(), angle);
}

float ComponentKinesisBody2D::getRotation()
{
	return body->m_body->GetAngle();
}


};
NEPHILIM_NS_END