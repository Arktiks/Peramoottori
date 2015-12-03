#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <scene\Component.h>

namespace pm
{	
	/** \brief Set GameEntity to be drawn.
	*
	* Description.
	*
	* \ingroup Scene
	*/

	class Drawable : public Component
	{
	public:

		/** \brief Default constructor
		*
		* By default Drawable is set to be drawn.
		*/
		Drawable() : Component(), drawState(true) {};

		/** \brief Change if GameEntity should be drawn.
		*
		* \param[in] newDrawState False if GameEntity should not be drawn.
		*/
		void SetDrawState(bool newDrawState) { drawState = newDrawState; }

		/** \brief Return state of Drawable.
		*
		* \return true if GameEntity is drawn.
		* \return false if GameEntity is not drawn.
		*/
		bool GetDrawState() { return drawState; }

	private:

		bool drawState;
	};
}

#endif //DRAWABLE_H