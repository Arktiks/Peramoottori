#ifdef _DEBUG
#define DEBUG_PM
#include "Debug_New.h"
#else 
#define DEBUG_PM new
#endif

#include <iostream>

Debug_PM::Debug_PM()
{
	count = 0;
}
Debug_PM::~Debug_PM()
{
	std::cout << "There are " << count << " unmatched new/deletes." << std::endl;
}
void Debug_PM::AddCount()
{
	count++;
}

void Debug_PM::MinusCount()
{
	count--;
}

Debug_PM* Debug_PM::Instance()
{
	if (instance == 0)
	{
		instance = new Debug_PM;
	}
	return instance;
}