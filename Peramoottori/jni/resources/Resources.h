#ifndef RESOURCES_H
#define RESOURCES_H

#include <structs\Engine.h>
#include <structs\LoadedImage.h>
#include <string>

// T‰ll‰ hetkell‰ filut luetaan assets -kansiosta AAssetManagerin kautta.
// Tehd‰‰n pian parempi ratkaisu.

class Resources
{
public:
	static char* TextReader(std::string fileName, Engine* engine);
	static LoadedImage* PNGReader(std::string fileName, Engine* engine);
};

#endif