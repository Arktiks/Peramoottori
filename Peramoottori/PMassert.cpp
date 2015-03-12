#include "System\PMassert.h"

void Assert(const char* file, const int line)
{
	// Log file and file
	__android_log_print(ANDROID_LOG_INFO, "ASSERTION_INFO", file, line);
	std::abort();
}