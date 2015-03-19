#ifndef RESOURCE_H
#define RESOURCE_H


#include <string>

namespace pm
{
	class Resource
	{
	public:

		Resource();
		void SetName(std::string name);
		std::string GetName();

		~Resource();

	private:

		std::string fileName;
	};
}
#endif //!RESOURCE_H
