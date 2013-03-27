#include "Nephilim/Clock.h"

#ifdef PARABOLA_DESKTOP
#include <SFML/System/Clock.hpp>
#elif defined PARABOLA_ANDROID
#include <time.h>
#elif defined PARABOLA_IPHONE
#include <mach/mach_time.h>
#endif

PARABOLA_NAMESPACE_BEGIN

////////////////////////////////////////////////////////////////////////// Time class
Time::Time(){
	m_microSeconds = 0;
}

Time::Time(Int64 microSeconds){
	m_microSeconds = microSeconds;
}

float Time::asSeconds(){
	return m_microSeconds / 1000000.f;
}

Int64 Time::asMiliSeconds(){	
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


Time Time::operator -(Time right)
{
	Time t;
	t.m_microSeconds = m_microSeconds - right.asMicroseconds();
	return t;
}





#ifdef PARABOLA_DESKTOP

class Clock::ClockImplementation{
public:
	sf::Clock clock;
};

#else
class Clock::ClockImplementation{
public:
	ClockImplementation(){
		myStartTime = getCurrentTime();
	}

	Time getCurrentTime(){
#ifdef PARABOLA_ANDROID
		timespec time;
		clock_gettime(CLOCK_MONOTONIC, &time);
		Time genTime;	
		genTime.m_microSeconds =  static_cast<Uint64>(time.tv_sec) * 1000000 + time.tv_nsec / 1000;
		return genTime;
#elif defined PARABOLA_IPHONE
    
        static mach_timebase_info_data_t frequency = {0,0};
        if(frequency.denom == 0)
            mach_timebase_info(&frequency);
        Uint64 nanoseconds = mach_absolute_time() * frequency.numer / frequency.denom;
        Time genTime;	
		genTime.m_microSeconds =  nanoseconds / 1000;
		return genTime;
        
#endif
	}

	Time myStartTime;
};
#endif



Clock::Clock(){
	myClockImpl = new ClockImplementation();
}

Clock::~Clock(){
	delete myClockImpl;
};

void Clock::pause(){

}

void Clock::start(){

}



void Clock::reset(){
#ifdef PARABOLA_DESKTOP
	myClockImpl->clock.restart();
#else
	myClockImpl->myStartTime = myClockImpl->getCurrentTime();
#endif
}

Time Clock::getElapsedTime(){

#ifdef PARABOLA_DESKTOP
	return Time::fromMicroseconds(myClockImpl->clock.getElapsedTime().asMicroseconds());
#else
	return myClockImpl->getCurrentTime() - myClockImpl->myStartTime;
#endif
};

PARABOLA_NAMESPACE_END