#include "Resource.h"

using namespace pm;

Resource::Resource()
{
}

void Resource::SetName(std::string name)
{
	fileName = name;
}
std::string Resource::GetName()
{
	return fileName;
}

Resource::~Resource()
{
}
