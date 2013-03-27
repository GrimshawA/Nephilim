#ifndef PARABOLA_KINESISACTORS_H
#define PARABOLA_KINESISACTORS_H

#include "Platform.h"

#include <Box2D/Box2D.h>
#include "Vectors.h"
class b2Body;
PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Kinesis
	\class KinesisBodyActor
	\brief Represents a body in a simulation
	
	Every body in the kinesis world has a 1:1 relationship with a KinesisBodyActor

*/
class PARABOLA_API KinesisBodyActor{
public:
	/// Creates a body actor from a body
	KinesisBodyActor(b2Body *body);

	/// Get the angle of rotation of the body
	float getAngle();

	/// Get angle in degrees, directly compatible with SFML
	float getDegreeAngle();

	void setVelocity(Vec2f velocity);

	Vec2f getVelocity();

	Vec2f getPosition();

	void setPosition(Vec2f position);

	/// Set the angle of rotation of the body, it is 0.f by default and is facing right, expressed in radians
	void setAngle(float radians);

	/// Choose whether this body is allowed to rotate
	void setFixedRotation(bool fixedRotation);

	b2Body* m_body;
	void* m_userdata;
};

/**
	\ingroup Kinesis
	\class KinesisBodyShape
	\brief Represents a shape(fixture) contained within a body.
*/
class KinesisBodyShape{
public:
	/// Construct the shape from the fixture
	KinesisBodyShape(b2Fixture* fix);
};

PARABOLA_NAMESPACE_END
#endif