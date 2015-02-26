#ifndef MEMORYTRACK_H
#define MEMORYTRACK_H

#include <cstddef>
#include <string>

struct MemoryTrack
{
public:
	void* pointer;
	size_t size;
	std::string filename; // File where new is called.
	int line; // Line where new is called.

	MemoryTrack() : pointer(nullptr), size(0), line(0) {};
	MemoryTrack(void* pointer, size_t size, std::string filename, int line) :
		pointer(pointer), size(size), filename(filename), line(line) {};
};

#endif