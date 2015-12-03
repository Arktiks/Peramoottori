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
		Name();
		Name(std::string newName);
		~Name();
		std::string GetName(){ return name; };
		void SetName(std::string newName){ name = newName; };
	private:
		std::string name;
	};
}
#endif

