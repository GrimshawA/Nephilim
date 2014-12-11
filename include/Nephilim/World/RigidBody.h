#ifndef NephilimWorldRigidBody_h__
#define NephilimWorldRigidBody_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Vectors.h>


NEPHILIM_NS_BEGIN

/**
	\class RigidBody
	\brief Wrapper for interacting with physics RigidBody instances

	This class does nothing by itself, its just an interface for 
	applying forces, impulses and other functions.

	In order for the functions to do anything, RigidBody must be inherited
	in a custom class, directly respective to its physics library.

	For example, when using Box2D, RigidBody will be interfacing with a b2Body
	for sure and when using PhysX or Bullet, it will act upon the respective rigid
	body instances.

	So, one RigidBody instance will be a single rigid body instance in a given physics library.
*/
class NEPHILIM_API RigidBody
{
public:
	
	/// Apply a force to the center of the rigid body
	virtual void applyForceToCenter(Vector2D force){}

	/// Apply a angular impulse to the object (2D)
	virtual void applyAngularImpulse(float impulse2d){}

	/// Set the rotation of the rigid body (2D)
	virtual void setRotation(float angle){}

	/// Get the rotation of the rigid body (2D)
	virtual float getRotation2D(){ return 0.f; }

	/// Enable or disable rigid body rotation
	virtual void setFixedRotation(bool enable){}
};

NEPHILIM_NS_END
#endif // NephilimWorldRigidBody_h__
