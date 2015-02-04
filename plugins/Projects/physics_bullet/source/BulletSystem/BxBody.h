#ifndef BxBody_h__
#define BxBody_h__

#include <Nephilim/Platform.h>

class btCollisionObject;

NEPHILIM_NS_BEGIN

/**
	\ingroup Physics
	\class BxBody
	\brief Wraps a bullet physics body
*/
class NEPHILIM_API BxBody
{
public:

	enum BodyType
	{
		RigidBody,
		SoftBody,
		GhostBody,
		PairCachingGhostBody,
		Other
	};

	BxBody();

	~BxBody();

/*private:*/
	btCollisionObject* m_body;
	BodyType m_type; ///< The type of the body to cast back to a full type
};

class NEPHILIM_API BxShape
{
public:

	
};

NEPHILIM_NS_END

#endif // BxBody_h__
