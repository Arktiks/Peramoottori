#ifndef SCENE_H
#define SCENE_H

#include "graphics\Shader.h"

namespace pm
{
	class Scene
	{
	public:
		Scene();
		void Update();
		void Draw();

	private:
		Shader shader;
	};
}

#endif //SCENE_H