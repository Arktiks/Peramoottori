#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <scene\Component.h>

namespace pm
{	
	/// GameEntity Component aka. boolean storage for one boolean.
	class Drawable : public Component
	{
	public:

		///Constructor
		Drawable() : Component(), drawState(true) {};

		/// Sets the draw state of component.
		void SetDrawState(bool newDrawState) { drawState = newDrawState; }

		/// Returns boolean that tels the draw state.
		bool GetDrawState() { return drawState; }

	private:

		bool drawState;

	};
}

#endif //DRAWABLE_H