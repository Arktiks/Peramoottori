#ifndef TIME_H
#define TIME_H

#include <time.h>

namespace pm
{
	class Time
	{
	public:
		Time();

		double calculateTimeInFrame();
		time_t rawTime;

		double timeInFrame;
		struct timespec start;
		struct timespec end;
		
		~Time();

	private:
		bool inFrame;

	};
}

#endif