#include "RNG.h"
#include <cstdlib>

bool RNG::Chance(int percentualSuccess)
{
	if ((rand() % 101) <= percentualSuccess)
		return true;
	else
		return false;
}

int RNG::Random(int max)
{
	return (rand() % (max + 1));
}

int RNG::RandomNotZero(int max)
{
	return ((rand() % max) + 1);
}

int RNG::Between(int min, int max)
{
	return (rand() % (min - max) + min);
}