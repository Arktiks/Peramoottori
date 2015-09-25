#ifdef _DEBUG
#ifndef PROFILERMANAGER_H
#define PROFILERMANAGER_H

#include <string>
#include <map>

namespace pm
{
	/** \brief Static class that manages Profiler objects and data they gather.
	* 
	* 1. Use PROFILE macro in every function you want to profile.
	*
	* 2. At start of main loop, use Clear() to reset the data.
	*
	* 3. At end of the loop, you can use Print() or AdvPrint() to print data gathered by Profiler objects.
	*
	* \note Profilers record time spend in scope of functions.
	* If you go from function to another without leaving the scope --- clock keeps on ticking.
	* For more complicated profiling, you need to use simple Print() and calculate the time by yourself.
	*
	* Example:
	*
	* You want to profile your rendering. Start with main render functions and profile each function used in render.
	* When you find the heaviest part, continue by profiling functions that you use in that function.
	* Continue the top-down aproach until you find the problem spots.
	*
	* \ingroup Debug
	*/

	class ProfilerManager
	{
	public:

		ProfilerManager() {};
		~ProfilerManager() {};
		
		/** \brief Print simple breakdown of all current data in store.
		*
		* \note Time spent in (functio) is: (time).
		*/
		static void Print();
		
		/** \brief Print advanced breakdown of all current data in store.
		*
		* \note Time spent in (function) is: (time), which is (percentage) percentage of total time.
		*/
		static void AdvPrint();
		
		/** \brief Clears data gathered by profilers.
		*
		* Use this function once in mainloop to gather data per full loop.
		*/
		static void Clear();

		/** \brief Function for Profiler objects to deliver data to ProfilerManager. */
		static void GatherData(std::string name, long double value);

	private:

		static std::map<std::string, long double> data; // All the data gathered by profilers.
	};
}

#endif
#endif