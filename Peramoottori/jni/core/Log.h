#ifdef _DEBUG
#ifndef DEBUG_LOG
#define DEBUG_LOG

#include <GLES2/gl2.h>

namespace pm
{
	/** \brief Tools used to print info into logcat.
	*
	* Logcat being android logging system.
	* %Log class functionality includes printing your own messages or catching possible OpenGL errors.
	*
	* \ingroup Debug
	*/

	class Log
	{
	public:

		/** @name Restricted Static Public Member Functions
		*  User should not use following restricted functions unless he is 100% confident of their purpose.
		*/
		///@{
		/**
		* \brief Writes messages into logcat under DEBUG_INFO.
		*
		* Works same as printf --- PrintInfo("These are numbers: %i %f", int, float);
		*/
		static void PrintInfo(const char* text...);

		/** \brief Write messages into logcat under DEBUG_WARNING.
		*
		* Works same as printf --- PrintWarning("These are numbers: %i %f", int, float);
		*/
		static void PrintWarning(const char* text...);

		/** \brief Write OpenGL errors into logcat.
		*
		* Goes through all glGetError() flags while formatting and printing them using DEBUG_WARNING.
		*/
		static bool PrintGLError(const char* file, const unsigned int line);

		/** \brief Clear possible OpenGL errors.
		*
		* Logic here is to clear error queue from earlier error messages that didn't crash the program,
		* so we can be 100% sure of our error handling on more critical parts.
		*/
		static void ClearGLError();
		///@}

	private:

		/// Formats received text into printf format.
		static char* FormatMessage(const char* text...);
	};
}

// Macros should be used instead of the direct functions.
#define DEBUG_INFO(text) pm::Log::PrintInfo text ///< Macro to print info into logcat.
#define DEBUG_WARNING(text) pm::Log::PrintWarning text ///< Macro to print warnings into logcat.

#define DEBUG_GL_ERROR() pm::Log::PrintGLError(__FILE__, __LINE__);///< Macro to print shader errors into logcat.
#define DEBUG_GL_ERROR_CLEAR() pm::Log::ClearGLError();///< Macro to print GL errors into logcat.

#endif // DEBUG_LOG
#endif // _DEBUG


// Disable logging for release version. 
#ifdef NDEBUG
#define DEBUG_INFO(text)
#define DEBUG_WARNING(text)

#define DEBUG_GL_ERROR(text)
#define DEBUG_GL_ERROR_CLEAR(text)
#endif