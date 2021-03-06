#pragma once
#include <scene\GameEntity.h>
#include <scene\Transformable.h>
#include <graphics\Rectangle.h>

class Box // Wrapper class for GameEntity.
{
public:
	Box();
	~Box();
	void Draw(); // Draw contained GameEntity.

	pm::Transformable* Transform(); // Handle to GameEntity Transformable.
	pm::Rectangle* Rectangle(); // Handle to GameEntity Rectangle.

	void ChangeTexture(std::string name); // Change texture on the fly.
	bool Contains(glm::vec2 coordinate); // If GameEntity overlaps with given coordinate.

	pm::GameEntity* entity;

	const float WIDTH = 200.f;
	const float HEIGHT = 200.f;
};