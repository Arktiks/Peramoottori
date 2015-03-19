#ifndef TIME_H
#define TIME_H

#include <time.h>

namespace pm
{
	class Time
	{
	public:
		Time() : inFrame(false), timeInFrame(0), rawTime(0) {};

		double CalculateTimeInFrame();

		time_t rawTime;
		double timeInFrame;
		struct timespec start;
		struct timespec end;

	private:
		bool inFrame;

	};
}

#endif