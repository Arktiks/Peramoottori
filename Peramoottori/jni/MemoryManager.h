#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <vector>
#include <structs\MemoryTrack.h>

namespace pm
{
	/// Keeps track of memory usage during debugging.
	/// Singleton class that is turned off for release.

	class MemoryManager
	{
	public:
		/// Static function that returns instance pointer of MemoryManager.
		///		\return pointer to only instance of this class.
		static MemoryManager* GetInstance();

		/// Deletes MemoryManager instance.
		/// Should be called once application is ready to close.
		static void DeleteInstance();

		/// Pushes MemoryTrack structs to memory vector.
		void AddTrack(MemoryTrack track);

		///
		void DeleteTrack(void* pointer);

	private:
		MemoryManager() {};
		~MemoryManager();

		static MemoryManager* instance;
		std::vector<MemoryTrack> memory;
	};
}

#endif