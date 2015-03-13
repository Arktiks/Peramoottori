#ifndef PMDEBUG_H
#define PMDEBUG_H

#include <android/log.h>
#include <cstdarg>
#include <cstdio>
#include <string>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "DEBUG_MSG", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "WARNING_MSG", __VA_ARGS__))

namespace pm
{
	class PMdebug
	{
	public:
		/**
		*Kirjoita viestisi jonka haluat nähdä Logcatissa DEBUG_MSG.
		*Toimii samanlailla kuin printf eli MsgInfo("%i %s %f", int, string, float);
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
		*Kirjoita viestisi jonka haluat nähdä Logcatissa DEBUG_MSG.
		*Toimii samanlailla kuin printf(string));
		*/
		static void MsgInfo(std::string string)
		{
			MsgInfo(string.c_str());
		}
		/**
		*Kirjoita viestisi jonka haluat nähdä Logcatissa WARNING_MSG.
		*Toimii samanlailla kuin printf eli MsgInfo("%i %s %f", int, string, float); jne
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
}

#endif