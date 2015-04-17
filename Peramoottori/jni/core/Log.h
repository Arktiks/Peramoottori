#ifdef _DEBUG
#ifndef DEBUG_LOG
#define DEBUG_LOG

#include <GLES2/gl2.h>

namespace pm
{
	/// Logging functions that our macros use.
	class Log
	{
	public:
		/// Writes messages into logcat under DEBUG_INFO.
		/// Works same as printf:
		///		PrintInfo("These are numbers: %i %f", int, float);
		static void PrintInfo(const char* text...);

		/// Writes messages into logcat under DEBUG_WARNING.
		static void PrintWarning(const char* text...);

		static void PrintGLShaderError(GLuint shader);

		static bool PrintGLError(const char* file, const unsigned int line);

		static void ClearGLError();

	private:
		/// Formats received text into printf format.
		static char* FormatMessage(const char* text...);
	};
}

// Macros should be used instead of the direct functions.
#define DEBUG_INFO(text) pm::Log::PrintInfo text ///< Macro to print info into logcat.
#define DEBUG_WARNING(text) pm::Log::PrintWarning text ///< Macro to print warnings into logcat.

#define DEBUG_GL_ERROR() pm::Log::PrintGLError(__FILE__, __LINE__);
#define DEBUG_GL_ERROR_CLEAR() pm::Log::ClearGLError();

#endif // DEBUG_LOG
#endif // _DEBUG


// Disable logging for release version. 
#ifdef NDEBUG
#define DEBUG_INFO void(0)
#define DEBUG_WARNING void(0)

#define DEBUG_GL_ERROR void(0)
#define DEBUG_GL_ERROR_CLEAR void(0)
#endif