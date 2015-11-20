#include "UpdateRate.h"


UpdateRate::UpdateRate()
{
	time = 0;
	updateRate = 0.1;
}
UpdateRate::UpdateRate(float updateRate)
{
	time = 0;
	this->updateRate = updateRate;
}


UpdateRate::~UpdateRate()
{
}
