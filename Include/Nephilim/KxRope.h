#ifndef KxRope_h__
#define KxRope_h__

#include "Platform.h"
#include "Vectors.h"

NEPHILIM_NS_BEGIN

class KxScene;

class NEPHILIM_API KxRopeBuilder{
public:	
	/// Make this compound a bridge (a few bodies, connected by joints)
	void createBridge(Vec2f bridgeStart, Vec2f bridgeEnd, int stepCount);

	/// Make this compound own a bridge
	void createRope(Vec2f ropeStart, float fraglen, int fragments);

	KxScene* sim;
};

NEPHILIM_NS_END
#endif // KxRope_h__
