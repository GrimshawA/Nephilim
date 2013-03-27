#ifndef PARABOLA_LOGGER_H
#define PARABOLA_LOGGER_H

#include "Platform.h"
#include "Strings.h"

#ifdef PARABOLA_ANDROID
#include "AndroidInterface.h"
#endif

PARABOLA_NAMESPACE_BEGIN

#ifdef PARABOLA_ANDROID
#define TESTLOG(x) __android_log_print(ANDROID_LOG_INFO, "ParabolaLogger", (x));
#define PRINTLOG(tag, formats, ...) __android_log_print(ANDROID_LOG_INFO, tag, formats, __VA_ARGS__);
/*#elif defined PARABOLA_BROWSER
static FILE* logFilePtr = fopen("K:/Users/Hellhound/Desktop/plugin_test/log.txt", "a");
#define TESTLOG(x) fprintf(logFilePtr, x);
#define PRINTLOG(tag, formats, ...) fprintf(logFilePtr, "[%s] ", tag);fprintf(logFilePtr, formats, __VA_ARGS__);*/
#else
#define TESTLOG(x) printf(x);
#define PRINTLOG(tag, formats, ...) printf("[%s] ", tag);printf(formats, __VA_ARGS__);
#endif

#define LOG(x) TESTLOG(x)

namespace LoggerSettings{
	/// Verbose modes of the logger
	/// A log is always output with a verbose mode
	/// It is shown in that verbose mode, and all the lower ones.
	enum Modes{
		NONE = 0, /// Nothing is output
		DETAIL, 
		NORMAL, /// 
		CRITICAL,
		FATAL, /// Only fatal errors are output
	};
};

/**
	\ingroup Core
	\class Logger
	\brief Ability to log information into multiple destinations
*/
class PARABOLA_API Logger{
public:

	/// Simply outputs the string into the stdout
	static void fastLog(const String &output);

private:
	bool myEnabled;
	LoggerSettings::Modes myVerboseMode;
};

#ifdef PARABOLA_BUILD_DEBUG
#define DEBUG_MESSAGE(x) Logger::fastLog(x);
#elif defined PARABOLA_BUILD_RELEASE
#define DEBUG_MESSAGE(x) 
#endif

PARABOLA_NAMESPACE_END
#endif