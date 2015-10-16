#ifdef _DEBUG
#ifndef PROFILER_H
#define PROFILER_H

#include <string>
#include <core\Time.h>

namespace pm
{	
	/** \brief Debug tool used to check how much time functions take to complete.
	*
	* Use macro PROFILE at start of function.
	* This creates new %Profiler that is destroyed when leaving function scope.
	* When %Profiler destructs it sends the name of the function and time spend in the function to the ProfilerManager.
	*
	* \ingroup Debug
	*/
	
	class Profiler
	{
	public:

		/** Used by PROFILE macro for profiling time spent in function. */
		Profiler(std::string functionName);

		~Profiler();

	private:

		Time clock;

		std::string name;
	};
}

/// Creates profiler and gives it the name of the function automatically.
#define PROFILE pm::Profiler(__FUNCTION__)

#endif // PROFILER_H
#endif // _DEBUG

// Disable profiler for release version. 
#ifdef NDEBUG
#define PROFILE
#endif