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

	for (const auto& funcs : functions)
		funcs();

	system("pause");
	return 0;
}