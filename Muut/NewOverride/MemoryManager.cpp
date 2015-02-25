#include "MemoryManager.h"

MemoryManager* MemoryManager::instance = nullptr;

MemoryManager* MemoryManager::GetInstance()
{
	if(instance == nullptr)
		instance = new MemoryManager;
	return instance;
}

MemoryManager::AddTrack()
{
}