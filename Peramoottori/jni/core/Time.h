#ifndef TIME_H
#define TIME_H

#include <time.h>

namespace pm
{
	class Time
	{
	public:

		///
		/// Constructor for Time.
		///
		Time() : inFrame(false), timeInFrame(0) { clock_gettime(CLOCK_MONOTONIC, &startTimer); };


		///
		/// Simple function to calculate time in frame or a loop.
		/// When function is called for the first time, it starts
		/// the timer, and when it's called second time and so on
		/// it calculates how long it took to call it again.
		///		\return double value how long the time between calls was.
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