#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <Box2D\Dynamics\b2World.h>

namespace pm
{
	class PhysicsSystem
	{
	public:

		static PhysicsSystem& Instance();
		
		~PhysicsSystem();

		void Update();

		b2World world;

	private:

		PhysicsSystem();

		const float32 STEP = 0.017f; // 60 times per second.

		const int32 VELOC_ITERATION = 6;

		const int32 POS_ITERATION = 2;
	};
}

#endif