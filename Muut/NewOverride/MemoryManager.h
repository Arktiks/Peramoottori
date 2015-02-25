#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <vector>

class MemoryManager
{
public:
	MemoryManager* GetInstance();
	void AddTrack(void* ptr);

private:
	MemoryManager() {};
	~MemoryManager() {};

	static MemoryManager* instance;
	std::vector<void*> memory;
};

#endif