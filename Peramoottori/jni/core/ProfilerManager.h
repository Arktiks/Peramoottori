#ifndef PROFILERMANAGER_H
#define PROFILERMANAGER_H

#include <string>
#include <map>

namespace pm
{
	/// Commentation!

	class ProfilerManager
	{
	public:

		ProfilerManager() {};
		~ProfilerManager() {};
		static void GatherData(std::string name, long double value);
		static void Print();
		static void AdvPrint();
		static void Clear();

	private:

		static std::map<std::string, long double> data;
	};
}

#endif