#ifndef PROFILER_H
#define PROFILER_H

#include <string>
#include "core\Time.h"
#include "core\Log.h"

#define PROFILE pm::Profiler(__FUNCTION__)

namespace pm
{
	class Profiler
	{
	public:
		Profiler(std::string funcName)
			:name(funcName)
		{
			clock.CalculateTimeInFrame();
		};

		~Profiler(){
			DEBUG_INFO(("Time spend in %c is: %f", name, clock.CalculateTimeInFrame());
		};
	private:
		Time clock;
		std::string name;
	};
}
#endif