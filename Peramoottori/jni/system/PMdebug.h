#ifndef PMDEBUG_H
#define PMDEBUG_H

#include <android/log.h>
#include <cstdarg>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "DEBUG_MSG", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "WARNING_MSG", __VA_ARGS__))

class PMdebug
{
public:
	/**
	*Kirjoita viestisi jonka haluat nähdä Logcatissa DEBUG_MSG.
	*/
	static void MsgInfo(const char* s...)
	{
		va_list args;
		va_start(args, s);

		char* tempString;

		vasprintf(&tempString, s, args);

		va_end(args);

		LOGI(tempString);
	};


	/**
	*Kirjoita viestisi jonka haluat nähdä Logcatissa WARNING_MSG.
	*/
	static void MsgWarning(const char* s...)
	{
		va_list args;
		va_start(args, s);

		char* tempString;

		vasprintf(&tempString, s, args);

		va_end(args);

		LOGW(tempString);
	};
};

#endif