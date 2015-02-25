/*#include <cstdlib>
#include <cstddef>
#include <new>
#include <iostream>
using namespace std;


void* operator new (unsigned int size, const char* file, int line)
{
	void* ptr = new char[size];
	cout << "size = " << size << " filename = " << file << " line = " << line << endl;
	return ptr;
}

#define new new(__FILE__, __LINE__)*/

#include "GlobalNew.h"

int main()
{
	int* x = new int;
	system("pause");
	return 0;
}