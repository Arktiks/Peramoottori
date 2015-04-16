#include "Log.h"
#include <android/log.h>
#include <core/Passert.h>

#include <cstdarg>
#include <cstdio>
#include <string>

using namespace pm;
using namespace std;

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "DEBUG_INFO", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "DEBUG_WARNING", __VA_ARGS__))

void Log::PrintInfo(const char* text...)
{
	char* tempInfo = FormatMessage(text);
	LOGI(tempInfo);
}

void Log::PrintWarning(const char* text...)
{
	char* tempWarning = FormatMessage(text);
	LOGW(tempWarning);
}

void Log::PrintGLShaderError(GLuint shader)
{
	GLint tempCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &tempCompiled);

	if (tempCompiled == 0) // Shader does not compile.
	{
		GLsizei tempLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tempLength);

		if (tempLength > 0)
		{
			GLsizei tempInfoLength = 0;
			string tempInfoLog(tempLength, ' ');

			glGetShaderInfoLog(shader, tempLength, &tempInfoLength, &tempInfoLog[0]);

			DEBUG_WARNING(("Shader not created!"));
			DEBUG_WARNING(("%s", tempInfoLog.c_str()));

			ASSERT(false);

			//GLchar* tempInfoBuffer;
			//free(infoBuf);
			//delete infoBuf;
		}
	}
}

void Log::PrintGLError(const char* file, const unsigned int line)
{
	GLenum tempError = GL_NO_ERROR;

	do // Loop as long as there are error flags.
	{
		tempError = glGetError(); // Get current error.

		if (tempError != GL_NO_ERROR)
			DEBUG_WARNING(("OpenGL error (%i) %s on line %s.", tempError, file, line));

	} while (tempError != GL_NO_ERROR);
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