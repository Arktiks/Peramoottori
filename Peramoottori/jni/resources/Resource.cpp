#include "Resource.h"
#include <System\PMassert.h>
#include <System\PMdebug.h>

using namespace pm;

Resource::Resource()
{
}

void Resource::ReadAsset(std::string fileName)
{
	int tempLen = fileName.length();

	std::string tempFileExtension = fileName.substr(fileName.size() - 4);
	//tempFileExtension.c_str();

	std::string tempTxt = ".txt";
	std::string tempTtf = ".ttf";
	std::string tempOgg = ".ogg";
	std::string tempPng = ".png";

	if (strcmp(tempFileExtension.c_str(), tempTxt.c_str()) == 0)
	{
		PMdebug::MsgInfo("TXT compare works");
		//assets.insert(std::make_pair<std::string, std::string>(fileName, ReadText(fileName)));

	}

	else if (strcmp(tempFileExtension.c_str(), tempTtf.c_str()) == 0)
	{
		PMdebug::MsgInfo("TTF compare works");
		//ReadFont
	}

	else if (strcmp(tempFileExtension.c_str(), tempOgg.c_str()) == 0)
	{
		PMdebug::MsgInfo("OGG compare works");
		//ReadSound
	}

	else if (strcmp(tempFileExtension.c_str(), tempPng.c_str()) == 0)
	{
		PMdebug::MsgInfo("PNG compare works");
		resourcemanager.ReadImage(fileName);
	}

	else
	{
		PMdebug::MsgWarning("File type not recognized");
	}
}


Resource::~Resource()
{
}
