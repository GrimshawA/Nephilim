#include <Nephilim/Foundation/Time.h>

NEPHILIM_NS_BEGIN

const Time Time::Zero = Time::fromSeconds(0.f);

Time::Time(){
		m_microSeconds = 0;
}

Time::Time(Int64 microSeconds){
	m_microSeconds = microSeconds;
}

float Time::asSeconds() const
{
	return static_cast<float>(m_microSeconds / 1000000.f);
}

Int64 Time::asMilliseconds(){
	return m_microSeconds / 10000.f;
};

Int64 Time::asMicroseconds(){
	return m_microSeconds;
}

// Static
Time Time::fromSeconds(float seconds){
	return Time((Int64)(seconds * 1000000.f));
};

// Build a Time object from an amount of miliseconds
Time Time::fromMiliSeconds(Int64 miliSeconds){
	return Time((Int64)(miliSeconds * 10000.f));
};

// Static
Time Time::fromMicroseconds(Int64 microSeconds){
	return Time(microSeconds);
};

/// Greater or equal operator for comparing times
bool Time::operator>=(const Time& right)
{
	return (m_microSeconds > right.m_microSeconds);
}

Time Time::operator -(Time right)
{
	Time t;
	t.m_microSeconds = m_microSeconds - right.asMicroseconds();
	return t;
}

/// Sum two time spans
Time Time::operator +(const Time& right)
{
	Time t;
	t.m_microSeconds = m_microSeconds + right.m_microSeconds;
	return t;
}

/// Increment by another time span
Time& Time::operator +=(const Time& right)
{
	this->m_microSeconds += right.m_microSeconds;
	return *this;
}

bool Time::operator!=(const Time& right) const
{
	return this->m_microSeconds != right.m_microSeconds;
}

bool Time::operator<=(const Time& right) const
{
	return this->m_microSeconds <= right.m_microSeconds;
}


NEPHILIM_NS_END
