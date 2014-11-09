#ifndef NephilimGesture_h__
#define NephilimGesture_h__

#include <Nephilim/Platform.h>

#include <sigc++/sigc++.h>

#include <vector>

NEPHILIM_NS_BEGIN
class Event;

/**
	\ingroup Core
	\class Gesture
	\brief Base class for gesture detectors
*/
class NEPHILIM_API Gesture
{
public:
	virtual void pushEvent(const Event& event) = 0;
};


class NEPHILIM_API PinchGesture : public Gesture
{
public:
	virtual void pushEvent(const Event& event);

	struct PointerInfo
	{
		float x, y;
		int id;
	};

	std::vector<PointerInfo> pressed_ids;
	float initial_distance;
	float last_distance;

	sigc::signal<void, float> onPinch;
};

NEPHILIM_NS_END
#endif // NephilimGesture_h__