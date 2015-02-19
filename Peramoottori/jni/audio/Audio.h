#ifndef AUDIO_H
#define AUDIO_H

#include "resources\ResourceReader.h"
#include <string>

namespace PM
{
	class Audio
	{
	public:
		Audio(std::string fileName);
		~Audio();

		int GetSize();
		char* GetData();

	private:

		std::vector<char> data;
		int size;
	};
}
#endif //AUDIO_H