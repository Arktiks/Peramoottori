#include "MemoryManager.h"
#include <iostream>
#include <fstream>

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

MemoryManager::~MemoryManager()
{
	if (!memory.empty()) // If there are undeleted tracks.
	{
		ofstream log("memoryleaks.txt");

		if (log.is_open())
		{
			log << "MEMORY LEAKS" << endl << "############" << endl;

			for (vector<MemoryTrack>::iterator it = memory.begin(); it != memory.end(); it++) // Iterate through memory leaks and write them.
			{
				cout << it->filename << " (" << it->line << ") : size (" << it->size << ")" << endl;
				log << it->filename << " (" << it->line << ") : size (" << it->size << ")" << endl; // FILENAME (LINE) : size (SIZE)
			}

			log.close();
		}
		else
			cout << "Couldn't open memoryleaks text." << endl;
	}
}