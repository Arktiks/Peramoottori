#ifndef DEBUGMSG_H

#define DEBUGMSG_H

#endif // !DEBUGMSG_H

#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "DEBUG_MSG", __VA_ARGS__))

class DebugMSG
{
public:
	/**
	*Kirjoita viestisi jonka haluat nähdä Logcatissa
	*/
	static void MSG(char* s)
	{
		LOGI(s);
	};
};