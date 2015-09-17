#include "Time.h"
#define BILLION 1000000000L

double pm::Time::CalculateTimeInFrame()
{
	if (inFrame == false) // Enters here only once, starting the timer.
	{	
		clock_gettime(CLOCK_MONOTONIC, &startFrameTimer);
		
		inFrame = true;

		return 0;
	}

	else if (inFrame == true) // Calculates the time difference since last call.
	{
		clock_gettime(CLOCK_MONOTONIC, &endFrameTimer);
		timeInFrame = BILLION * (endFrameTimer.tv_sec - startFrameTimer.tv_sec) + (endFrameTimer.tv_nsec - startFrameTimer.tv_nsec);
		startFrameTimer = endFrameTimer;
	
		return timeInFrame;
	}
	return 0;
}

double pm::Time::GetCurrentTime()
{
	double tempCurrent = clock_gettime(CLOCK_REALTIME, &startTimer);
	return tempCurrent = (tempCurrent - clock_gettime(CLOCK_MONOTONIC, &startTimer)) / BILLION;
}