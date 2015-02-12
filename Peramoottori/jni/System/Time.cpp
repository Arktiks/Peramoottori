#include "Time.h"


PM::Time::Time()
{
}

double PM::Time::calculateTimeInFrame()
{
	frameStart = clock_gettime(CLOCK_MONOTONIC, NULL);


	bool tempInFrame = true;

	if (tempInFrame == false)
	{
		frameStart = clock_gettime(CLOCK_MONOTONIC, NULL);
		tempInFrame = true;
	}

	tempInFrame = false;

	return timeInFrame = difftime(frameStart, frameEnd);

}

PM::Time::~Time()
{
}
