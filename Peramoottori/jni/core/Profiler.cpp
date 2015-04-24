#include "Profiler.h"
#include <core\Log.h>

using namespace std;
using namespace pm;

Profiler::Profiler(string functionName) : name(functionName)
{
	clock.CalculateTimeInFrame();
}

Profiler::~Profiler()
{
	float time = clock.CalculateTimeInFrame();
	DEBUG_INFO(("Time spent in %s is: %f", name.c_str(), time));
}