#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <vector>
#include "MemoryTrack.h"

class MemoryManager
{
public:
	static MemoryManager* GetInstance();
	static void DeleteInstance();
	void AddTrack(MemoryTrack track);
	void DeleteTrack(void* pointer);

private:
	MemoryManager() {};
	~MemoryManager();

	static MemoryManager* instance;
	std::vector<MemoryTrack> memory;
};

#endif