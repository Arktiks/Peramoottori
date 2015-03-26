#include "TestClass.h"
#include <core\Log.h>
#include <core\Application.h>

using namespace pm;

TestClass::TestClass()
{
	Application::AddContextFunction(Initialize);
}

bool TestClass::Initialize()
{
	DEBUG_INFO(("INITIALIZING TESTCLASS"));
	return true;
}

TestClass::~TestClass()
{
}