#include <Nephilim/Logger.h>

#include <stdarg.h>
#include <stdio.h>

#ifdef NEPHILIM_ANDROID
#include <Nephilim/AndroidInterface.h>
#include <android/log.h>
#endif

NEPHILIM_NS_BEGIN

Logger NLog;

String Logger::m_tag = "Nephilim";

void Log(const char * format, ...)
{
	char buffer[256];
	va_list args;
	va_start (args, format);
	vsprintf (buffer,format, args);
	va_end (args);

#ifdef NEPHILIM_ANDROID
	__android_log_print(ANDROID_LOG_INFO, Logger::m_tag.c_str(), buffer);
#else
	printf("[%s] %s\n", Logger::m_tag.c_str(), buffer);
#endif
}

Logger& Logger::operator<<(const String& s)
{
	printf("%s", s.c_str());
	return *this;
}

NEPHILIM_NS_END