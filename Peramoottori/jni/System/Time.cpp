#include "Time.h"


pm::Time::Time()
{
	inFrame = false;
	timeInFrame = 0;
	rawTime = 0;
}

double pm::Time::calculateTimeInFrame()
{

	if (inFrame == false)
	{	
		rawTime = clock_gettime(CLOCK_MONOTONIC, &now);

		inFrame = true;
		
		return 0;
	}

	else if (inFrame == true)
	{

		clock_gettime(CLOCK_MONOTONIC, &then);

		timeInFrame = difftime(then.tv_sec, now.tv_sec) * 1000000000LL + difftime(then.tv_nsec, now.tv_nsec);

		now = then;
	
		return timeInFrame;
	}

	return 0;
}

pm::Time::~Time()
{
}
