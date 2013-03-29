#ifndef PARABOLA_KINESISCONTACTLISTENER_H
#define PARABOLA_KINESISCONTACTLISTENER_H

#include "Platform.h"
#include <Box2D/Box2D.h>

NEPHILIM_NS_BEGIN

/**
	\ingroup Kinesis
	\class KinesisContactListener
	\brief An interface to detect collisions in a Kinesis simulation.


*/
class NEPHILIM_API KinesisContactListener : public b2ContactListener{
public:
	/// Called when a 
	virtual void BeginContact (b2Contact *contact);	
	/// Called when a 
	virtual void EndContact(b2Contact *contact);
	/// Called when a 
	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
	/// Called when a 
	virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
};
NEPHILIM_NS_END
#endif