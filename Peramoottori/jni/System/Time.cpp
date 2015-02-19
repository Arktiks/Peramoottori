#include "Time.h"


PM::Time::Time()
{
	inFrame = false;
	timeInFrame = 0;
	rawTime = 0;
}

double PM::Time::calculateTimeInFrame()
{
	//clock_gettime(CLOCK_MONOTONIC, &now);
	time(&rawTime);

	if (inFrame == false)
	{	
		frameStart = clock_gettime(CLOCK_MONOTONIC, &now);

		inFrame = true;
		
		return 0;
	}

	else if (inFrame == true)
	{
	//	clock_gettime(CLOCK_MONOTONIC, &now);
	//	frameEnd = now.tv_nsec;

		timeInFrame = difftime(rawTime, now.tv_sec) * 1000000000LL + now.tv_nsec;

		frameStart = clock_gettime(CLOCK_MONOTONIC, &now);

		return timeInFrame;
	}

	return 0;
}

PM::Time::~Time()
{
}
