#ifndef NephilimTime_h__
#define NephilimTime_h__

#include "Platform.h"

NEPHILIM_NS_BEGIN

class Clock;

/**
	\ingroup Foundation
	\class Time
	\brief Holds a time span, internally represented in microseconds, but convertible to other types.

	This class is valuable when working with time. Because it works with big integers, it takes a LOT of time
	to lose precision. If a float value was used, the bigger it would get the precision issues would rise.

	This fact, allied with the fixed time steps, allow for huge precision and also allows the user to use a float value in the range of seconds,
	so it is usually easier to make calculations with time.

	Disclaimer: This class is heavily under the influence of the equivalent sf::Time, in the SFML2 library.
	Credits to Laurent Gomila, the original author.
*/
class NEPHILIM_API Time
{
public:
	/// Creates a null time span
	Time();

	/// Creates a time span with the given micro seconds
	Time(Int64 microSeconds);

	/// Convert the time span to seconds, where 1 second returns 1.0
	float asSeconds() const;

	/// Convert the time spawn to miliseconds, where 1000 miliseconds = 1 second
	Int64 asMiliSeconds();

	/// Returns the time span
	Int64 asMicroseconds();

	/// Build a Time object from an amount of microseconds
	static Time fromMicroseconds(Int64 microSeconds);

	/// Build a Time object from an amount of miliseconds
	static Time fromMiliSeconds(Int64 miliSeconds);

	/// Build a Time object from an amount of seconds
	static Time fromSeconds(float seconds);

	/// Greater or equal operator for comparing times
	bool operator>=(const Time& right);

	/// Minus operator overload to subtract time spans
	Time operator -(Time right);

	/// The time span representation
	Int64 m_microSeconds;
	friend class Clock;

	static const Time Zero;
};

NEPHILIM_NS_END
#endif // NephilimTime_h__
