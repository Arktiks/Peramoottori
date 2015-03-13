#include "Passert.h"
#include "Log.h"

#include <assert.h>
#include <cstdlib>

using namespace pm;

void Passert::Assert(const char* file, const int line)
{
	DEBUG_WARNING(("ASSERT FAILED: %s (%i)", file, line));
	//__android_log_print(ANDROID_LOG_INFO, "ASSERTION_INFO", file, line); // Log filename and line number.
	std::abort(); // Causes abnormal program termination.
}