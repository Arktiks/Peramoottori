#ifdef _DEBUG
#ifndef GLOBALNEW_H
#define GLOBALNEW_H

#pragma comment(linker, "/nodefaultlib:libc.lib")
#pragma comment(linker, "/nodefaultlib:libcd.lib")

#include <iostream>

void* operator new (size_t size, const char* file, int line)
{
	void* ptr = new char[size];
	std::cout << "New: " << file << " (" << line << ")" << std::endl;
	return ptr;
}

void *operator new[](size_t size, const char *file, int line)
{
	return operator new(size, file, line);
}

void operator delete(void *ptr)
{
	free(ptr);
}

void operator delete[](void *ptr)
{
	operator delete(ptr);
}

#define new new(__FILE__, __LINE__)

#endif
#endif