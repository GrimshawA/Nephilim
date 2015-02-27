#ifndef NephilimUxEvent_h__
#define NephilimUxEvent_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

class UxNode;

/**
	\class UxEvent
	\brief An event that goes down the UX hierarchy to be handled by the nodes
*/
class NEPHILIM_API UxEvent
{
public:
	int type;

	/// The node who emitted this event
	UxNode* emitter;

	union
	{
		int a;
	};
};

NEPHILIM_NS_END
#endif // NephilimUxEvent_h__
