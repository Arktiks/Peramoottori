#include "GlobalNew.h"

int main()
{
	int* a = NEW int(23);
	char* b = NEW char('b');
	double* c = NEW double(23.1);

	delete a;

	//MemoryManager::GetInstance()->DeleteInstance();
	MemoryManager::DeleteInstance();

	system("pause");
	return 0;
}