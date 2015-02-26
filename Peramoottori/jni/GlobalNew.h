#ifdef _DEBUG
#ifndef GLOBALNEW_H
#define GLOBALNEW_H

//#pragma comment(linker, "/nodefaultlib:libc.lib")
//#pragma comment(linker, "/nodefaultlib:libcd.lib")

#include <iostream>
#include <string>
#include "MemoryManager.h"
#include "MemoryTrack.h"

void* operator new (size_t size, const char* file, int line)
{
	void* ptr = new char[size]; // Make void* pointer based on size.
	std::string filename = std::string(file); // Convert filename to string.
	MemoryTrack track(ptr, size, filename, line); // Make struct of it.
	MemoryManager::GetInstance()->AddTrack(track); // Make note of memory track.
	std::cout << "New: " << file << " (" << line << ")" << std::endl; // Debug info.
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

#define NEW new(__FILE__, __LINE__)

#endif
#endif


#ifdef NDEBUG

#define NEW new

#endif