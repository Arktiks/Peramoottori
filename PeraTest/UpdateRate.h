#pragma once
#include <scene\Component.h>
class UpdateRate :
	public pm::Component
{
public:
	UpdateRate();
	UpdateRate(float updateRate);
	~UpdateRate();
	float time;
	float updateRate;
};

