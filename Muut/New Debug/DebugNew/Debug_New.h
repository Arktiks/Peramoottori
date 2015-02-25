#ifdef _DEBUG
#ifndef DEBUG_PM_H
#define DEBUG_PM_H

#include <iostream>

class Debug_PM
{
public:
	static Debug_PM* Instance();
	void AddCount();
	void MinusCount();
		
protected:
	Debug_PM();
	~Debug_PM();

private:
	int count;
	static Debug_PM* instance;

};


void* operator new (size_t size, const char* file, int line)
{
	void *p = malloc(size);
	std::cout << "Allocated @" << file << ", " << line << std::endl;
	Debug_PM::Instance()->AddCount();
	return p;
};
void* operator new[](size_t size, const char* file, int line)
{
	void *p = malloc(size);
	std::cout << "Allocated @" << file << ", " << line << std::endl;
	Debug_PM::Instance()->AddCount();
	return p;
};

void operator delete (void* p, const char* file, int line)
{
	std::free(p);
	std::cout << "Released @" << file << ", " << line << std::endl;
	Debug_PM::Instance()->MinusCount();
};

void operator delete[](void* p, const char* file, int line)
{
	std::free(p);
	std::cout << "Released @" << file << ", " << line << std::endl;
	Debug_PM::Instance()->MinusCount();
};
#endif DEBUG_NEW_H
#endif _DEBUG