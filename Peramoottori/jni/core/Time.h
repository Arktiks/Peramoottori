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
		
		Time() : inFrame(false), timeInFrame(0), rawTime(0) {};

		/** \brief Calculate time in frame or loop.
		*
		* When called for the first time Time objects internal timer starts ticking.
		* When called second time and onward elapsed time between calls is calculated.
		* \return Elapsed time between calls in milliseconds.
		*/
		double CalculateTimeInFrame();

	private:

		time_t rawTime;
		double timeInFrame;
		struct timespec start;
		struct timespec end;
		bool inFrame;
	};
}

#endif