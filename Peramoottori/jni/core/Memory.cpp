#include "Memory.h"
#include "Log.h"

#include <new>
#include <stdio.h>
#include <cstdio>
#include <string>

using namespace std;
using namespace pm;

vector<MemoryTrack> Memory::memory; // Define our static memory vector.

void Memory::AddTrack(MemoryTrack track)
{
	memory.push_back(track);
}

void Memory::DeleteTrack(void* pointer)
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

void Memory::WriteLeaks()
{
	if (!memory.empty()) // If there are undeleted tracks.
	{
		DEBUG_WARNING(("::: MEMORY LEAKS :::"));

		for (vector<MemoryTrack>::iterator it = memory.begin(); it != memory.end(); it++) // Iterate through memory leaks and write them on logcat.
		{
			DEBUG_WARNING(("%s (%i) : size (%i)", it->filename.c_str(), it->line, it->size));
		}
	}
}



///////////////////////////////////////////////////////
///		Definitions for new and delete operators	///
///////////////////////////////////////////////////////

void* operator new (size_t size, const char* file, int line)
{
	void* ptr = new char[size]; // Make void* pointer based on size.
	std::string filename = std::string(file); // Convert filename to string.
	MemoryTrack track(ptr, size, filename, line); // Make struct of it.
	Memory::AddTrack(track); // Make note of memory track.
	return ptr; // Return pointer as per normal.
}

void *operator new[](size_t size, const char* file, int line)
{
	return operator new(size, file, line); // Use above function.
}

void operator delete(void* ptr)
{
	Memory::DeleteTrack(ptr); // Remove track from manager.
	free(ptr); // Free pointer as per normal.
}

void operator delete[](void* ptr)
{
	operator delete(ptr);
}