#ifndef TIME_H
#define TIME_H

#include <time.h>

namespace pm
{
	/** \brief Class to calculate elapsed time within your android %application.
	*
	* \ingroup Core
	*/

	class Time
	{
	public:
		
		///
		///
		Time() : inFrame(false), timeInFrame(0) { clock_gettime(CLOCK_MONOTONIC, &startTimer); };

		* When called for the first time Time objects internal timer starts ticking.
		* When called second time and onward elapsed time between calls is calculated.
		* \return Elapsed time between calls in milliseconds.
		*/
		///
		double CalculateTimeInFrame();
		
		double GetCurrentTime();


	private:

		double timeInFrame;
		struct timespec startTimer;
		struct timespec startFrameTimer;
		struct timespec endFrameTimer;
		bool inFrame;
	};
}

#endif