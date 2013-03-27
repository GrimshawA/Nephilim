#include "Nephilim/KinesisActors.h"
#include "Nephilim/KinesisWorld.h"
#include <Box2D/Box2D.h>
#include <Nephilim/MMath.h>

PARABOLA_NAMESPACE_BEGIN

/// Creates a body actor from a body
KinesisBodyActor::KinesisBodyActor(b2Body *body) : m_userdata(NULL){
	m_body = body;
};

/// Get the angle of rotation of the body
float KinesisBodyActor::getAngle(){
	return m_body->GetAngle();
};

void KinesisBodyActor::setPosition(Vec2f position){
	m_body->SetTransform(b2Vec2(((KinesisWorld*)m_body->GetWorld())->ToMeters(position.x), ((KinesisWorld*)m_body->GetWorld())->ToMeters(position.y)), m_body->GetAngle());
};


Vec2f KinesisBodyActor::getPosition(){
	return Vec2f(((KinesisWorld*)m_body->GetWorld())->ToPixels(m_body->GetPosition().x), ((KinesisWorld*)m_body->GetWorld())->ToPixels(m_body->GetPosition().y));
};

Vec2f KinesisBodyActor::getVelocity(){
	return Vec2f(m_body->GetLinearVelocity().x, m_body->GetLinearVelocity().y);
};

/// Get angle in degrees, directly compatible with SFML
float KinesisBodyActor::getDegreeAngle(){
	return Math::radianToDegree(m_body->GetAngle());
};

void KinesisBodyActor::setVelocity(Vec2f velocity){
	m_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
};

/// Set the angle of rotation of the body, it is 0.f by default and is facing right, expressed in radians
void KinesisBodyActor::setAngle(float radians){
	m_body->SetTransform(m_body->GetPosition(), radians);
};

/// Choose whether this body is allowed to rotate
void KinesisBodyActor::setFixedRotation(bool fixedRotation){
	m_body->SetFixedRotation(fixedRotation);
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/// Construct the shape from the fixture
KinesisBodyShape::KinesisBodyShape(b2Fixture* fix){

};

PARABOLA_NAMESPACE_END
