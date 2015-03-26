#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

namespace pm
{
	class Circle : public virtual Shape
	{
	public:

		Circle(float radius, int iterations);
		~Circle();

	private:

		int smoothness;
		float radius;

	};
}

#endif