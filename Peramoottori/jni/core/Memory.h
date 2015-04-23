#ifdef _DEBUG // Debug version has been defined.
#ifndef DEBUG_MEMORY
#define DEBUG_MEMORY

#include <vector>
#include <structs\MemoryTrack.h>


// Uncomment these if there are linker errors.
// #pragma comment(linker, "/nodefaultlib:libc.lib") 
// #pragma comment(linker, "/nodefaultlib:libcd.lib")


namespace pm
{
	/// Keeps track of memory usage during debugging.
	class Memory
	{
	public:
		/// Pushes MemoryTrack structs to memory vector.
		///		\param track : MemoryTrack information.
		static void AddTrack(MemoryTrack track);

		/// Removes MemoryTrack structs from memory vector based on provided pointer.
		///		\param pointer : void* universal pointer.
		static void DeleteTrack(void* pointer);

		/// Prints memory leaks to logcat.
		/// Should be called when app is destroyed.
		///		\return true if there are leaks.
		static void WriteLeaks();

	private:
		static std::vector<MemoryTrack> memory; ///< Vector keeping track of called new and delete operator.
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