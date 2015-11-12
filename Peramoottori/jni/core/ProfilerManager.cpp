#include "ProfilerManager.h"
#include <core\Profiler.h>
#include <core\Log.h>

#ifdef _DEBUG 
using namespace pm;
using namespace std;

std::map<std::string, long double> ProfilerManager::data = { { "initializing", 0.0f } };

void ProfilerManager::GatherData(std::string name, long double value)
{
	data[name] = value;
}

void ProfilerManager::Print()
{
	map <string, long double>::iterator it;
	for (it = data.begin(); it != data.end(); ++it)
		DEBUG_INFO(("Time spent in %s is: %f.", it->first.c_str(), it->second));
}

void ProfilerManager::Clear()
{
	data.clear();
}

void ProfilerManager::AdvPrint()
{
	map <string, long double>::iterator it;
	long double total = 0;

	for (it = data.begin(); it != data.end(); ++it)
		total += it->second;

	for (it = data.begin(); it != data.end(); ++it)
	{
		long double percentage = (it->second / total) * 100;
		DEBUG_INFO(("Time spent in %s is: %f, which is %f percentage of total time.", it->first.c_str(), it->second, percentage));
	}
}
#endif