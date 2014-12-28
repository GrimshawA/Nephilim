#ifndef NephilimClock_h__
#define NephilimClock_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Time.h>

NEPHILIM_NS_BEGIN
/**
	\ingroup Foundation
	\class Clock
	\brief Capable of handling time by giving the period of time elapsed since the last reset

	Disclaimer: This class is heavily under the influence of the equivalent sf::Time, in the SFML2 library.
	Credits to Laurent Gomila, the original author.
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
#endif // NephilimClock_h__
