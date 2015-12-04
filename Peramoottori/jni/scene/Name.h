#ifndef NAME_H
#define NAME_H
#include <string>
#include <scene\Component.h>
namespace pm
{
	/** \internal No commentation what so ever
	*/
	class Name : public Component
	{
	public:

		/** \brief constructor
		*/
		Name();

		/** \brief constructor
		* \param[in] std::string name name of the component
		*/
		Name(std::string newName);
		/** \brief destructor
		*/
		~Name();

		/** \brief get name
		* \return std::string name name of the component
		*/
		std::string GetName(){ return name; };

		/** \brief set name
		* \param[in] std::string name name of the component
		*/
		void SetName(std::string newName){ name = newName; };


	private:

		std::string name;
	};
}
#endif

