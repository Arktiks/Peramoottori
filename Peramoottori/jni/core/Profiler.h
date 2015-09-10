#ifndef PROFILER_H
#define PROFILER_H

#include <string>
#include <core\Time.h>

namespace pm
{	
	/// Profiler to check how much time functions take to complete.
	// HOW TO: Use the PROFILE macro at start of function.
	// This creates a new profiler that self destructs when leaving the scope.
	// When the Profiler destructs, it sends the name of the function and time spend in the function to the profiler manager.
	class Profiler
	{
	public:
		/// Used by PROFILE macro for profiling the time spend in function..
		Profiler(std::string functionName);

		~Profiler();

	private:

		Time clock;

		std::string name;
	};
}
/// Creates a profiler and gives it the name of the function automatically.
#define PROFILE pm::Profiler(__FUNCTION__)

#endif