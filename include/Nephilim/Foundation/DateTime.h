#ifndef NephilimDateTime_h__
#define NephilimDateTime_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

NEPHILIM_NS_BEGIN

/**
	\class DateTime
	\brief Provides tools to manipulate dates and times.

	What if you wanted to get a time stamp of the local time?
	\code
		cout<<DateTime::timeStamp()<<endl;
	\endcode
	Easy as it looks. Prints '2003-06-22T20:57:29' as an example.
*/
class NEPHILIM_API DateTime
{
private:
	/// Members of the date time
	int h, m, s, ms;

public:
	/// Creates a DateTime object
	DateTime();

	/// Defines this DateTime object as the current system date and time
	void setFromLocalTime();

	/// Get the hour
	int hour();

	/// Get the minute
	int minute();

	/// Get the second
	int second();

	/// Get the milisecond
	int milisecond();

	/// Returns a timeStamp of the local time on the format 'yyyy-mm-ddThh:mm::ss'
	static String timeStamp();

	/// Returns a string like 00:00:00 with the given time
	static String createTimeString(int minutes, int seconds);
};


NEPHILIM_NS_END
#endif // NephilimDateTime_h__