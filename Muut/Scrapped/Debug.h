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


/// Debug functions that our macros use.
/// Never use these functions directly!


/// Overload new and delete operators to track memory leaks.
/// Functions are defined in .cpp to avoid compilation errors.
extern void* operator new(size_t size, const char* file, int line);
extern void* operator new[](size_t size, const char* file, int line);
extern void operator delete(void* ptr);
extern void operator delete[](void* ptr);


/// Debug macros for printing messages and asserting.
/// These should be used instead of the direct functions.
#define NEW new(__FILE__, __LINE__) ///< Macro to use overloaded new.



#endif // DEBUG_TOOLS
#endif // _DEBUG

