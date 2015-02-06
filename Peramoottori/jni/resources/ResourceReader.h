#ifndef RESOURCEREADER_H
#define RESOURCEREADER_H

#include <structs\Engine.h>
#include <structs\LoadedImage.h>
#include <string>

#include <tr1\shared_ptr.h>
#include <tr1\memory>
#include <memory>
#include <memory.h>

// T‰ll‰ hetkell‰ filut luetaan assets -kansiosta AAssetManagerin kautta.
// Tehd‰‰n pian parempi ratkaisu.

class ResourceReader
{
public:
	static ResourceReader& GetInstance();
	virtual ~ResourceReader();
	

	char* TextReader(std::string fileName, Engine* engine);
	LoadedImage* PNGReader(std::string fileName, Engine* engine);

private:
	

};

#endif