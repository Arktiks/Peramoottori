#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <scene\Component.h>

namespace pm
{
	class Drawable : public Component
	{
	public:
		Drawable() : Component()
		{
			drawState = true;
		};

		void SetDrawState(bool newDrawState)
		{
			drawState = newDrawState;
		};
		bool GetDrawState()
		{
			return drawState;
		};

	private:
		bool drawState;

	};
}

#endif //DRAWABLE_H