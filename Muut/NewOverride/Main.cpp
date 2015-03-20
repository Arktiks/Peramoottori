#include <cstdlib>
#include <new>
#include <iostream>
//#include <Windows.h>
using namespace std;


/////////////////////////////////////////////////////////////
//Start
/////////////////////////////////////////////////////////////
static const char *fname_delete;
static int lineno_delete;

void *operator new(size_t, const char *, int);
void *operator new[](size_t, const char *, int);
void operator delete(void *);
void operator delete[](void *);
void deletep(const char *, int);

void *operator new(size_t size, const char *file, int lineno)
{
	void *pfs = malloc(size);
	if(NULL == pfs)
	{
		cerr << "no heap to allocate" << endl;
		exit(-1);
	}
	cout << "newed at file " << file;
	cout << " at line " << lineno << " for ";
	cout << /*hex << pfs << dec <<*/ "size " << (int)size << endl;
	return pfs;
}

void *operator new[](size_t size, const char *file, int lineno)
{
	return operator new(size, file, lineno);
}

void operator delete(void *pfs)
{
	free(pfs); // free pointer
	cout << "deleted at file " << fname_delete;
	cout << " at line " << lineno_delete << endl;
	//cout << " deleted for " << hex << pfs << dec << endl;
	return;
}

void operator delete[](void *pfs)
{
	operator delete(pfs);
}

void deletep(const char *file, int lineno)
{
	fname_delete = file;
	lineno_delete = lineno;
	return;
}

#define new new(__FILE__, __LINE__)
#define delete deletep(__FILE__, __LINE__), delete
/////////////////////////////////////////////////////////////
//End
/////////////////////////////////////////////////////////////


class aclass
{
private:
	int num;
	char mychar;
public:
	aclass(int num, char mychar) : num(num), mychar(mychar) {}
	aclass() { num = 0; mychar = 'a'; }
	void output() { cout << num << " " << mychar << endl; }
};


int main()
{
	int *a = new int(100);
	aclass *b = new aclass(100, 'b');
	aclass *c = new aclass[2];
	//b->output();
	//c[0].output();
	//c[1].output();

	delete a;
	delete b;
	delete[] c;
	system("PAUSE");
	return 0;
}