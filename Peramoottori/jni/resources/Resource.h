#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

namespace pm
{
	
	/** \brief Base class to all resource types.
	*
	* Long description.
	*
	* \ingroup Resources
	*/

	class Resource
	{
	public:

		void SetName(std::string name) { fileName = name; }

		std::string GetName() { return fileName; }

		virtual ~Resource() {};

	protected:

		Resource() {}; // Resource is never created directly.

		Resource(std::string name) : fileName(name) {};

	private:

		std::string fileName;

	};
}

#endif // RESOURCE_H