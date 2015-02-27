#include "Memory.h"
using namespace std;

char Memory::delete_name = '\0';
int Memory::delete_line = 0;
Memory* Memory::instance = nullptr;

Memory* Memory::GetInstance()
{
	if(instance == nullptr)
		instance = new Memory;
	return instance;
}