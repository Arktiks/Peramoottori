#ifdef _DEBUG // Debug version has been defined.
#ifndef DEBUG_MEMORY
#define DEBUG_MEMORY

#include <vector>
#include <structs\MemoryTrack.h>

// Uncomment these if there are linker errors.
#pragma comment(linker, "/nodefaultlib:libc.lib") 
#pragma comment(linker, "/nodefaultlib:libcd.lib")

namespace pm
{
	/** \brief Debug tool designed to keep track of memory usage during debugging.
	* \ingroup Debug
	*/

	class Memory
	{
	public:

		/** \brief Make note of called operator new
		*
		* \param[in] track MemoryTrack information.
		*/
		static void AddTrack(MemoryTrack track);

		/** \brief Note that previously called new has been properly deleted.
		* 
		* \param pointer void* universal pointer.
		*/
		static void DeleteTrack(void* pointer);

		/** \brief Print tracks that have not been deleted to logcat.
		*
		* Is called when Application closes without exceptions, but can also
		* be called when you want.
		*/
		static void WriteLeaks();

	private:

		static std::vector<MemoryTrack> memory;  // Vector keeping track of called new and delete operator.
	};
}


/// Overload new and delete operators to track memory leaks.
/// Functions are defined in .cpp to avoid compilation errors.
extern void* operator new(size_t size, const char* file, int line);
extern void* operator new[](size_t size, const char* file, int line);
extern void operator delete(void* ptr);
extern void operator delete[](void* ptr);

#define NEW new(__FILE__, __LINE__) ///< Overloaded new macro.

#endif // DEBUG_MEMORY
#endif // _DEBUG


// Disable memory tracking for release.
#ifdef NDEBUG

namespace pm
{
	class Memory
	{
	public:

		static void WriteLeaks() {}; // Temporary fix to compiler errors.

	};
}

#define NEW new
#endif