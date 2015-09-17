#ifndef PROFILERMANAGER_H
#define PROFILERMANAGER_H

#include <string>
#include <map>

namespace pm
{
	/// Manages profilers.
	// A static class that manages the profilers and data that they gather.
	// How to use:
	// 1. Use the PROFILE macro in every function you want to profile.
	// 2. At start of main loop, use Clear to reset the data.
	// 3. At end of the loop, you can use Print or AdvPrint to print out the data gathered by Profilers.
	// Notes: The profiler records the time spend in the scope of the function.
	// If you go from function to another without leaving the scope the clock keeps on ticking.
	// For more complicated profilings, you need to use simple Print and calculate the time by yourself.
	// Example:
	// You want to profile your render. Start with the main render function and profile each function used in render.
	// When you find the heaviest part, continue by profiling functions that you use in that function.
	// Continue the top-down aproach until you find the problem spots.
	class ProfilerManager
	{
	public:

		ProfilerManager() {};
		~ProfilerManager() {};
		
		///Prints simple format data for time spend in specific functions.
		static void Print();
		
		///Prints the breakdown of all the current data in store.
		static void AdvPrint();
		
		///Clears the data gathered by a profiler.
		// Use this function once in mainloop to gather data per full loop.
		static void Clear();

		///Function for Profilers to deliver the data to ProfilerManager.
		static void GatherData(std::string name, long double value);

	private:
		/// All the data gathered by profilers.
		static std::map<std::string, long double> data;
	};
}

#endif