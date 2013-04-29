#ifndef Logger_h__
#define Logger_h__

#include "Platform.h"
#include "Strings.h"

NEPHILIM_NS_BEGIN

/// Logs a simple formatted string
void Log(const char * format, ...);

/**
	\ingroup Core
	\class Logger
	\brief Process-wide logger

	If you are looking for more focused and configurable logging, use X instead. (TODO)
*/
class NEPHILIM_API Logger{
public:
	/// The tag prefix for Log()
	static String m_tag;
};

NEPHILIM_NS_END
#endif // Logger_h__
