#include "Time.h"


PM::Time::Time()
{
	inFrame = false;
	timeInFrame = 0;
	rawTime = 0;
}

double PM::Time::calculateTimeInFrame()
{
	time(&rawTime);

	if (inFrame == false)
	{	
		clock_gettime(CLOCK_MONOTONIC, &now);
		frameStart = rawTime;

		inFrame = true;
		
		return 0;
	}

	else if (inFrame == true)
	{
	//	clock_gettime(CLOCK_MONOTONIC, &now);
	//	frameEnd = now.tv_nsec;

		timeInFrame = difftime(rawTime, frameStart)*1000;

		frameStart = rawTime;

		return timeInFrame;
	}

	return 0;
}

PM::Time::~Time()
{
}
