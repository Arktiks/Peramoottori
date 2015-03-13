#ifdef _DEBUG // Debug version has been defined.
#ifndef DEBUG_TOOLS
#define DEBUG_TOOLS

#include <assert.h>
#include <string>
#include <structs/MemoryTrack.h>
#include "MemoryManager.h"


// Uncomment these if there are linker errors.
// #pragma comment(linker, "/nodefaultlib:libc.lib") 
// #pragma comment(linker, "/nodefaultlib:libcd.lib")


/////////////////////////////////////////////////////////////////////
//		Overload new and delete operators to track memory leaks.
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
/////////////////////////////////////////////////////////////////////


/// Debug functions that our macros use.
/// Never use these functions directly!
class Debug
{
public:
	Debug() {};

	/// Writes messages into logcat under DEBUG_INFO.
	/// Works same as printf:
	///		PrintInfo("These are numbers: %i %f", int, float);
	static void PrintInfo(const char* text...);

	/// Writes messages into logcat under DEBUG_WARNING.
	static void PrintWarning(const char* text...);

	/// Assert function to be used with the custom assert macros.
	static void Assert(const char* file, const int line);

	~Debug() {};

private:
	/// Formats received text into printf format.
	static char* FormateMessage(const char* text...);
};


/////////////////////////////////////////////////////////////////////
//		Debug macros for printing messages and asserting.
/////////////////////////////////////////////////////////////////////
#define NEW new(__FILE__, __LINE__) ///< Macro to use overloaded new.
#define DEBUG_INFO(text) Debug::PrintInfo text ///< Macro to print info into logcat.
#define DEBUG_WARNING(text) Debug::PrintWarning text ///< Macro to print warnings into logcat.
#define ASSERT(expression) \ !(expression) ? Debug::Assert(__FILE__, __LINE__) ///< Program aborts if expression == false.
#define ASSERT_EQUAL(expression1, expression2) \ expression1 != expression2 ? Debug::Assert(__FILE__, __LINE__) ///< Program aborts if expression1 != expression2.
#define ASSERT_NEQUAL(expression1, expression2) \ expression1 == expression2 ? Debug::Assert(__FILE__, __LINE__) ///< Program aborts if expression1 == expression2.
#define ASSERT_MINMAX(expression1, expression2, value) \ expression1 < value && value < expression2 ? Debug::Assert(__FILE__, __LINE__) ///< Program aborts if value is not between expression1 and expression2.
/////////////////////////////////////////////////////////////////////


#endif // DEBUG_TOOLS
#endif // _DEBUG


#ifdef NDEBUG // Release version has been defined.
#define NEW new
#define DEBUG_INFO void(0)
#define DEBUG_WARNING void(0)
#define ASSERT void(0)
#endif // NDEBUG