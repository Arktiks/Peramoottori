#include "Debug.h"
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <android/log.h>







/////////////////////////////////////////////////////////////////////
//		Definitions for new and delete operators.
/////////////////////////////////////////////////////////////////////

void* operator new (size_t size, const char* file, int line)
{
	void* ptr = new char[size]; // Make void* pointer based on size.
	std::string filename = std::string(file); // Convert filename to string.
	MemoryTrack track(ptr, size, filename, line); // Make struct of it.
	MemoryManager::GetInstance()->AddTrack(track); // Make note of memory track.
	return ptr; // Return pointer as per normal.
}

void *operator new[](size_t size, const char* file, int line)
{
	return operator new(size, file, line); // Use above function.
}

void operator delete(void* ptr)
{
	MemoryManager::GetInstance()->DeleteTrack(ptr); // Remove track from manager.
	free(ptr); // Free pointer as per normal.
}

void operator delete[](void* ptr)
{
	operator delete(ptr);
}