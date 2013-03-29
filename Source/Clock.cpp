#include <Nephilim/Clock.h>

#ifdef PARABOLA_WINDOWS
#include <windows.h>
#elif defined NEPHILIM_UNIX
#include <time.h>
#elif defined PARABOLA_IPHONE
#include <mach/mach_time.h>
#endif

namespace
{
#ifdef PARABOLA_WINDOWS
	LARGE_INTEGER getFrequency()
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		return frequency;
	}
#endif
}

NEPHILIM_NS_BEGIN

////////////////////////////////////////////////////////////////////////// Time class
Time::Time(){
	m_microSeconds = 0;
}

Time::Time(Int64 microSeconds){
	m_microSeconds = microSeconds;
}

float Time::asSeconds(){
	return static_cast<float>(m_microSeconds / 1000000.f);
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

Time getCurrentTime(){

#ifdef PARABOLA_WINDOWS
	// Force the following code to run on first core
	// (see http://msdn.microsoft.com/en-us/library/windows/desktop/ms644904(v=vs.85).aspx)
	HANDLE currentThread = GetCurrentThread();
	DWORD_PTR previousMask = SetThreadAffinityMask(currentThread, 1);

	// Get the frequency of the performance counter
	// (it is constant across the program lifetime)
	static LARGE_INTEGER frequency = getFrequency();

	// Get the current time
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	// Restore the thread affinity
	SetThreadAffinityMask(currentThread, previousMask);

	// Return the current time as microseconds
	return Time(1000000 * time.QuadPart / frequency.QuadPart);

#endif

#ifdef NEPHILIM_UNIX
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

	// There is no implementation for this system, the symptom is that times are all 0
	return Time(0);
}




Clock::Clock()
: m_last(getCurrentTime())
{
	
}

void Clock::reset()
{
	m_last = getCurrentTime();
}

Time Clock::getElapsedTime()
{
	return getCurrentTime() - m_last;
}

NEPHILIM_NS_END
