#ifndef TIME_H
#define TIME_H

#include <time.h>

namespace pm
{
	class Time
	{
	public:
		Time() : inFrame(false), timeInFrame(0), rawTime(0) {};


		/// Simple function to calculate time in frame or a loop.
		/// When function is called for the first time, it starts
		/// the timer, and when it's called second time and so on
		/// it calculates how long it took to call it again.
		///		\return double value how long the time between calls was.
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