#ifndef NephilimFoundationClock_h__
#define NephilimFoundationClock_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Time.h>

NEPHILIM_NS_BEGIN

/**
	\class Clock
	\brief Allows to track time with high resolution counters
*/
class NEPHILIM_API Clock
{
private:
	/// The last time we registered, necessary to figure out the elapsed time
	Time m_last;

public:
	/// Constructs the timer with current time
	/// so getElapsedTime() starts with 0
	Clock();

	/// Restarts the timer
	void reset();

	/// Get the elapsed time since the last call
	Time getElapsedTime();
};

NEPHILIM_NS_END
#endif // NephilimFoundationClock_h__
