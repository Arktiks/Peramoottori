#ifndef AUDIORESOURCE_H
#define AUDIORESOURCE_H

#include <resources\Resource.h>

namespace pm
{

	/** \internal Functions should be described with more detail. */

	/** \brief
	*
	* Long description.
	*
	* \ingroup Resources
	*/

	class AudioResource : public Resource
	{

		friend class Audio;

	public:
		
		/* I assume default constructor is not supported. */
		/** \brief Disabled default constructor.
		*/
		AudioResource() = delete;

		/**\brief Audio resource constructor.
		*
		* \param[in] fileDescriptorData Identifier that AudioManager uses to define files.
		* \param[in] aLength Length of the AudioResourse.
		* \param[in] aStart Length that is distance to start.
		*/
		AudioResource(int fileDescriptorData, off_t aLength, off_t aStart)
		: fileDescriptor(fileDescriptorData), length(aLength), start(aStart) {};

		/** \brief
		*
		* \return int FileDescriptor that AudioManager uses to define files.
		*/ 
		int GetFileDescriptor() { return fileDescriptor; };

		/** \brief
		*
		* \return off_t Length of AudioResourse.
		*/
		off_t GetLength() { return length; };

		/** \brief
		*
		* \return off_t Length that is distance to start.
		*/
		off_t GetStart(){ return start; };

		/** \brief Default destructor.
		*/
		~AudioResource() {};

	private:

		int fileDescriptor;

		off_t length, start;

	};
}

#endif // AUDIORESOURCE_H