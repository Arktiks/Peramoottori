#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
//#include <android\asset_manager.h>

namespace pm
{
	/// Mother class of all Resources
	class Resource
	{
	public:

		Resource() {}; 
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

		/// Deconstructor
		~Resource() {};

	private:

		std::string fileName;

	};
}

#endif //!RESOURCE_H