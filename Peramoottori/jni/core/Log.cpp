#include "Log.h"
#include <android/log.h>
#include <cstdarg>
#include <cstdio>

using namespace pm;

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "DEBUG_INFO", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "DEBUG_WARNING", __VA_ARGS__))

void Log::PrintInfo(const char* text...)
{
	char* tempInfo = FormatMessage(text);
	LOGI(tempInfo);
	//delete tempInfo;
}

void Log::PrintWarning(const char* text...)
{
	char* tempWarning = FormatMessage(text);
	LOGW(tempWarning);
	//delete tempWarning;
}

void Log::PrintGLError(GLuint shader)
{
	GLint compiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		if (length > 0)
		{
			GLint infoLength = 0;
			char* infoBuf;

			glGetShaderInfoLog(shader, length, &infoLength, infoBuf);

			DEBUG_INFO(("%s", infoBuf));

			//free(infoBuf);
			delete infoBuf;
		}
		DEBUG_WARNING(("Shader not created!"));
	}
}

char* Log::FormatMessage(const char* text...)
{
	char* tempBuffer = nullptr; // Buffer to hold our formatted string.

	va_list arguments; // Type to hold information about variable arguments.
	va_start(arguments, text); // Initialize a variable argument list.

	vasprintf(&tempBuffer, text, arguments); // Composes string with the same text that would be printed if format was used on printf.

	va_end(arguments); // End using variable argument list.
	return tempBuffer;
}