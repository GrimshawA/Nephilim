#ifndef DATETIME_H
#define DATETIME_H

#include "Platform.h"
#include "Strings.h"


PARABOLA_NAMESPACE_BEGIN
	/**
		\ingroup Foundation
		\class DateTime
		\brief Provides tools to manipulate dates and times.

		What if you wanted to get a time stamp of the local time?
		\code
			cout<<DateTime::timeStamp()<<endl;
		\endcode
		Easy as it looks. Prints '2003-06-22T20:57:29' as an example.
	*/
	class PARABOLA_API DateTime{
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

	private:
		int h,m,s,ms;
	};


PARABOLA_NAMESPACE_END
#endif