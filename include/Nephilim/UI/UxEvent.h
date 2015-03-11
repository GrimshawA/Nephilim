#ifndef NephilimUxEvent_h__
#define NephilimUxEvent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Event.h>

#include <stdint.h>

NEPHILIM_NS_BEGIN

class UxNode;

/**
	\class UxEvent
	\brief An event that goes down the UX hierarchy to be handled by the nodes
*/
class NEPHILIM_API UxEvent
{
public:
	enum EventType
	{
		Thing,
		NativeEvent,
		KeyPress,
		KeyRelease
	};

	int type;

	/// The node who emitted this event
	UxNode* emitter;

	Event _event;

	union
	{
		int a;
	};
};

/**
	\class UxKeyEvent
	\brief Subclass of UxEvent for keyboard events
*/
class NEPHILIM_API UxKeyEvent : public UxEvent
{
public:
	Keyboard::Key key;
	uint32_t unicode;

public:

	/// Construct initial state
	UxKeyEvent();
};


NEPHILIM_NS_END
#endif // NephilimUxEvent_h__
