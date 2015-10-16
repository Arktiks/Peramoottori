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

		/// Function to set a name for a resource.
		///
		/// This function is used by the spesific resource classes.
		///		@param name : string name of the file
		///
		void SetName(std::string name) { fileName = name; }

		/// Function to get a name of a resource
		///
		///		@return name of the resource
		///
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