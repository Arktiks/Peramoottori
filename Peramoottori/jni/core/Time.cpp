#include "Time.h"



pm::Time::Time(std::clock_t start)
{
	_start = start;
}


pm::Time::~Time()
{
}

double pm::Time::Restart()
{
	return Restart(SECONDS);
}

double pm::Time::Restart(FRACTION fraction)
{
	double tempTime = GetElapsedTime(fraction);
	_start = std::clock();

	return tempTime;
}

void pm::Time::Start()
{
	_start = std::clock();
}

double pm::Time::GetElapsedTime(FRACTION time)
{
	double tempElapsed;
	switch (time)
	{

	case SECONDS:
		tempElapsed = (std::clock() - _start) / (double)CLOCKS_PER_SEC;
		return tempElapsed;
		break;

	case MILLISECONDS:
		tempElapsed = (std::clock() - _start) / (double)(CLOCKS_PER_SEC / 1000.0);
		return tempElapsed;
		break;

	case MICROSECONDS:
		tempElapsed = (std::clock() - _start) / (double)(CLOCKS_PER_SEC / 1000000.0);
		return tempElapsed;
		break;
	}

}