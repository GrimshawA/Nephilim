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
public:
	Clock();

	void reset();
	Time getElapsedTime();

private:
	Time m_last;
};

NEPHILIM_NS_END
#endif // NephilimFoundationClock_h__
