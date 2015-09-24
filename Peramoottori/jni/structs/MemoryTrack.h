#ifndef MEMORYTRACK_H
#define MEMORYTRACK_H

#include <cstddef>
#include <string>

/** \brief Struct to hold information where new operator is called. Used in conjunction with pm::Memory class. */

struct MemoryTrack
{
public:
	void* pointer; ///< Pointer to data called by new.
	size_t size; ///< Size of data type.
	std::string filename; ///< File where new is called.
	int line; ///< Line number where new is called.

	/// Default constructor.
	MemoryTrack() : pointer(nullptr), size(0), line(0) {}; 

	/// Constructor that initializes all struct values.
	MemoryTrack(void* pointer, size_t size, std::string filename, int line) : 
		pointer(pointer), size(size), filename(filename), line(line) {}; 
};

#endif