#pragma once
#include "pmScene.h"
class IceScene:public pmScene
{
public:
	
	IceScene();
	~IceScene();

	void Update();
	void InitializeResources();
	void InitializeGameEntities();
	void UpdateGameEntities(float time);
};
