#include <Nephilim/Foundation/DateTime.h>

#include <ctime>
#ifdef NEPHILIM_WINDOWS
#include <windows.h>
#endif

#include <stdio.h>

NEPHILIM_NS_BEGIN

DateTime::DateTime()
{
}

String DateTime::createTimeString(int minutes, int seconds)
{
	String minString = String::number(minutes);
	if (minString.length() == 1)
		minString.insert(minString.begin(), '0');

	String secString = String::number(seconds);
	if (secString.length() == 1)
		secString.insert(secString.begin(), '0');

	return minString + ":" + secString;
}


	String DateTime::timeStamp(){
		time_t ltime;
		struct tm *Tm;

		ltime=time(NULL);
		Tm=localtime(&ltime);

		char buffer[20];
		if(Tm){
			sprintf(buffer, "%.4d-%.2d-%.2dT%.2d_%.2d_%.2d\0",
				Tm->tm_year+1900,
				Tm->tm_mon+1,
				Tm->tm_mday,
				Tm->tm_hour,
				Tm->tm_min,
				Tm->tm_sec);
		}

		return String(buffer);
	};

	int DateTime::hour(){
		return h;
	};
	int DateTime::minute(){
		return m;
	};
	int DateTime::second(){
		return s;
	};
	int DateTime::milisecond(){
		return ms;
	};

	void DateTime::setFromLocalTime(){
	#ifdef NEPHILIM_WINDOWS
		SYSTEMTIME systemtime;

		GetSystemTime(&systemtime);

		h = systemtime.wHour;
		m = systemtime.wMinute;
		s = systemtime.wSecond;
		ms = systemtime.wMilliseconds;

	#endif
	};

NEPHILIM_NS_END
