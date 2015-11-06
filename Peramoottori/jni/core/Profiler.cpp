#include "Profiler.h"
#include <core\ProfilerManager.h>
#include <core\Log.h>

using namespace pm;

Profiler::Profiler(std::string functionName) : name(functionName)
{
	clock.Start();
}

Profiler::~Profiler()
{
	long double time = clock.GetElapsedTime(Time::SECONDS);
	ProfilerManager::GatherData(name, time);
	DEBUG_INFO(("Time spent in %s is: %f seconds", name.c_str(), time));
}