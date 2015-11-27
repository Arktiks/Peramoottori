#include "Name.h"


pm::Name::Name() 
	: name(""), pm::Component()
{
}

pm::Name::Name(std::string newName)
	: name(newName), pm::Component()
{ 
}


pm::Name::~Name()
{
}
