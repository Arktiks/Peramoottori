#pragma once
#include "Scene.h"
#include <vector>

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Update();
	void AddScene(Scene* scene);
	void DeleteScene(std::string name);
	void ChangeScene(Scene* scene);
	Scene* GetScene(std::string name);
	bool Paused(); // Check if all scenes are paused.

	std::vector<Scene*> scenes;
	bool sceneChanged;
};