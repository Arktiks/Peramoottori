#include "Profiler.h"
#include "core\ProfilerManager.h"

using namespace pm;

Profiler::Profiler(std::string functionName) : name(functionName)
{
	clock.CalculateTimeInFrame();
}

Profiler::~Profiler()
{
	long double time = clock.CalculateTimeInFrame();
//	ProfilerManager::GatherData(name, time);
	//DEBUG_INFO(("Time spent in %s is: %f", name.c_str(), time));
}