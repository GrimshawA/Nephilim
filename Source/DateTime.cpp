#include "Nephilim/DateTime.h"
#include <ctime>
#ifdef NEPHILIM_WINDOWS
#include <windows.h>
#endif

#include <stdio.h>

NEPHILIM_NS_BEGIN

	DateTime::DateTime(){

	};

	String DateTime::timeStamp(){
		time_t ltime;
		struct tm *Tm;

		ltime=time(NULL);
		Tm=localtime(&ltime);

		char buffer[20];
		if(Tm){
			sprintf(buffer, "%.4d-%.2d-%.2dT%.2d:%.2d:%.2d\0",
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
