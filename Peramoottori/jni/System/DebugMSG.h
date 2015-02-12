#ifndef DEBUGMSG_H

#define DEBUGMSG_H

#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "DEBUG_MSG", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_INFO, "WARNING_MSG", __VA_ARGS__))

class PMDebugMSG
{
public:
	/**
	*Kirjoita viestisi jonka haluat nähdä Logcatissa DEBUG_MSG:na
	*/
	static void MsgInfo(const char* s...)
	{

		va_list args;
		va_start(args, s);

		char* temp_string;

		vasprintf(&temp_string, s, args);

		va_end(args);

		LOGI(temp_string);
	};
	/**
	*Kirjoita viestisi jonka haluat nähdä Logcatissa WARNING_MSG:na
	*/
	static void MsgWarning(const char* s...)
	{

		va_list args;
		va_start(args, s);

		char* temp_string;

		vasprintf(&temp_string, s, args);

		va_end(args);

		LOGE(temp_string);
	};
};
#endif // !DEBUGMSG_H