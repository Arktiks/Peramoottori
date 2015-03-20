/*#include <Printer.h>
#include <Windows.h>

int main()
{
print("Hello world!");
system("PAUSE");
return 0;
}*/

#include <vector>
#include <iostream>
#include <Windows.h>
using namespace std;

static vector<void(*)()> functions;

void func1()
{
	cout << "tekstia lel" << endl;
}

void func2()
{
	cout << "lisaa tekstia" << endl;
}

int main()
{
	functions.push_back(func1);
	functions.push_back(func2);

	//for (const auto& funcs : functions)
	//funcs();

	/*for (vector<void(*)()>::iterator it = functions.begin(); it != functions.end(); it++)
	{
	it;
	it = functions.erase(it);
	}*/

	for (auto it = functions.begin(); it != functions.end();)
	{

		(*it)();
		it = functions.erase(it);

		//void (*haha)();
		//haha = *it;
		//haha();
		//*it;
		//it();
		//functions.erase(functions.begin());
	}

	system("pause");
	return 0;
}