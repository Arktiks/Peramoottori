#include "MemoryManager.h"
#include <iostream>
#include <stdio.h>
#include <cstdio>
//#include <system\PMdebug.h>

using namespace std;
using namespace pm;

MemoryManager* MemoryManager::instance = nullptr;

MemoryManager* MemoryManager::GetInstance()
{
	if(instance == nullptr)
		instance = new MemoryManager;
	return instance;
}

void MemoryManager::DeleteInstance()
{
	//WriteLeaks();
	delete instance;
	instance = nullptr;
}

void MemoryManager::AddTrack(MemoryTrack track)
{
	memory.push_back(track);
}

void MemoryManager::DeleteTrack(void* pointer)
{
	if (!memory.empty())
	{
		for (vector<MemoryTrack>::iterator it = memory.begin(); it != memory.end(); it++) // Search through all tracks.
		{
			if (pointer == it->pointer) // If pointers match.
			{
				memory.erase(it); // Remove track from manager.
				break;
			}
		}
	}
}

bool MemoryManager::WriteLeaks()
{
	if (!memory.empty()) // If there are undeleted tracks.
	{
		//PMdebug::MsgWarning("::: MEMORY LEAKS :::");

		for (vector<MemoryTrack>::iterator it = memory.begin(); it != memory.end(); it++) // Iterate through memory leaks and write them on logcat.
		{
			//PMdebug::MsgWarning("%s (%i) : size (%i)", it->filename.c_str(), it->line, it->size);
		}
	}
}