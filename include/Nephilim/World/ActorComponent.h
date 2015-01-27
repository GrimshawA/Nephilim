#ifndef NephilimWorldActorComponentBase_h__
#define NephilimWorldActorComponentBase_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class ActorComponent
	\brief This is the base class for the Actor components

	The main difference between Component and ActorComponent
	is that ActorComponent has virtual tables due to some
	polymorphic API.
*/
class ActorComponent
{
public:
	virtual void damn(){}
};

NEPHILIM_NS_END
#endif // NephilimWorldActorComponentBase_h__
