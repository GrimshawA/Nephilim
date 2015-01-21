#ifndef NephilimFoundationLogger_h__
#define NephilimFoundationLogger_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

NEPHILIM_NS_BEGIN

/// Logs a simple formatted string
void Log(const char * format, ...);

/**
	\class Logger
	\brief Process-wide logger

	If you are looking for more focused and configurable logging, use X instead. (TODO)
*/
class NEPHILIM_API Logger
{
public:
	/// The tag prefix for Log()
	static String m_tag;

	Logger& operator<<(const String& s);
};

extern Logger NLog;

NEPHILIM_NS_END
#endif // NephilimFoundationLogger_h__
