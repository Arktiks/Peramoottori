#ifndef TIME_H
#define TIME_H

#include<time.h>

namespace PM
{
	class Time
	{
	public:
		Time();

		double calculateTimeInFrame();
		time_t rawTime;
		time_t frameStart;
		time_t frameEnd;
		double timeInFrame;
		struct timespec now;


		~Time();

	private:
		bool inFrame;

	};
}

#endif