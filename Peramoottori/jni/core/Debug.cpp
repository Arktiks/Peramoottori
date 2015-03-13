#include "Debug.h"
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "DEBUG_INFO", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "DEBUG_WARNING", __VA_ARGS__))


void Debug::PrintInfo(const char* text...)
{
	char* tempInfo = FormateMessage(text);
	LOGI(tempInfo);
	delete tempInfo;
}

void Debug::PrintWarning(const char* text...)
{
	char* tempWarning = FormateMessage(text);
	LOGI(tempWarning);
	delete tempWarning;
}

void Assert(const char* file, const int line)
{
	__android_log_print(ANDROID_LOG_INFO, "ASSERTION_INFO", file, line); // Log filename and line number.
	std::abort(); // Causes abnormal program termination.
}

char* Debug::FormateMessage(const char* text...)
{
	char* tempBuffer = nullptr; // Buffer to hold our formatted string.

	va_list arguments; // Type to hold information about variable arguments.
	va_start(arguments, text); // Initialize a variable argument list.

	vasprintf(&tempBuffer, text, arguments); // Composes string with the same text that would be printed if format was used on printf.

	va_end(arguments); // End using variable argument list.
	return tempBuffer;
}