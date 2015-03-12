#include "MemoryManager.h"
#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <system\PMdebug.h>

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
		for (vector<MemoryTrack>::iterator it = memory.begin(); it != memory.end(); it++) // Search through all new calls.
		{
			if (pointer == it->pointer) // If pointers match.
			{
				memory.erase(it); // Remove the track from manager.
				break;
			}
		}
	}

	//cout << "Couldn't delete track." << endl;
}

bool MemoryManager::WriteLeaks()
{
	if (!memory.empty()) // If there are undeleted tracks.
	{
		PMdebug::MsgWarning("::: MEMORY LEAKS :::");

		for (vector<MemoryTrack>::iterator it = memory.begin(); it != memory.end(); it++) // Iterate through memory leaks and write them on logcat.
		{
			PMdebug::MsgWarning("%s (%i) : size (%i)", it->filename.c_str(), it->line, it->size); // FILENAME (LINE) : size (SIZE)
		}
	}
}

MemoryManager::~MemoryManager()
{
	WriteLeaks();
}

/*if (!memory.empty()) // If there are undeleted tracks.
{
//const string &name = "memoryleaks.txt";
ofstream log("memoryleaks.txt", ios::out);
log.clear();
//if (log.is_open())
if (!log.fail())
{
log << "MEMORY LEAKS" << endl << "############" << endl;

for (vector<MemoryTrack>::iterator it = memory.begin(); it != memory.end(); it++) // Iterate through memory leaks and write them.
{
cout << it->filename << " (" << it->line << ") : size (" << it->size << ")" << endl;
log << it->filename << " (" << it->line << ") : size (" << it->size << ")" << endl;
}

log.close();
}
else
cout << "Couldn't open memoryleaks text." << endl;
}

FILE* file = fopen("/internal/memoryleak.txt", "w+");
if (file != NULL)
{
	fputs("hei", file);
	fflush(file);
	fclose(file);
}
else
{
}*/