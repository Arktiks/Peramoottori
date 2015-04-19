#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
//#include <android\asset_manager.h>

namespace pm
{
	class Resource
	{
	public:

		Resource() {};

		void SetName(std::string name) { fileName = name; }

		std::string GetName() { return fileName; }

		~Resource() {};

	private:

		std::string fileName;

	};
}

#endif //!RESOURCE_H