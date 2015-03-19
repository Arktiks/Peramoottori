#ifndef RESOURCE_H
#define RESOURCE_H

#include "ResourceManager.h"
#include <android\asset_manager.h>
#include <resources\Image.h>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <iostream>


namespace pm
{
	class Resource
	{
	public:
		ResourceManager resourcemanager;


		Resource();

		void ReadAsset(std::string fileName);

		~Resource();
	};
}
#endif //!RESOURCE_H
