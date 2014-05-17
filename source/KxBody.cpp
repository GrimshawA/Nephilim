#include <Nephilim/KxBody.h>
#include <Nephilim/KxScene.h>

#include <Box2D/Box2D.h>
#include <Nephilim/NxMath.h>

NEPHILIM_NS_BEGIN

/// Creates a body actor from a body
KxBody::KxBody(b2Body *body) : m_userdata(NULL)
{
	m_body = body;
};

/// Get the angle of rotation of the body
float KxBody::getAngle(){
	return m_body->GetAngle();
};

void KxBody::setPosition(Vec2f position)
{
	position.x = scene->toMeters(position.x);
	position.y = scene->toMeters(position.y);

	m_body->SetTransform(b2Vec2(position.x, position.y), m_body->GetAngle());
}


Vec2f KxBody::getPosition()
{
	return vec2(scene->toPixels(m_body->GetPosition().x), scene->toPixels(m_body->GetPosition().y) );
}

Vec2f KxBody::getVelocity(){
	return Vec2f(m_body->GetLinearVelocity().x, m_body->GetLinearVelocity().y);
};

/// Get angle in degrees, directly compatible with SFML
float KxBody::getDegreeAngle(){
	return math::radianToDegree(m_body->GetAngle());
};

void KxBody::setVelocity(Vec2f velocity)
{
	m_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

/// Set the angle of rotation of the body, it is 0.f by default and is facing right, expressed in radians
void KxBody::setAngle(float radians)
{
	m_body->SetTransform(m_body->GetPosition(), radians);
}

/// Choose whether this body is allowed to rotate
void KxBody::setFixedRotation(bool fixedRotation)
{
	m_body->SetFixedRotation(fixedRotation);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/// Construct the shape from the fixture
KinesisBodyShape::KinesisBodyShape(b2Fixture* fix)
{

};

NEPHILIM_NS_END
