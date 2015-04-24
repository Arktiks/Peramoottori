#ifndef PROFILER_H
#define PROFILER_H

#include <string>
#include <core\Time.h>

namespace pm
{
	class Profiler
	{
	public:

		Profiler(std::string functionName);

		~Profiler();

	private:
		Time clock;
		std::string name;
	};
}

#define PROFILE pm::Profiler(__FUNCTION__)

#endif