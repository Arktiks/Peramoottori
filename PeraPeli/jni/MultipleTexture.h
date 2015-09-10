#pragma once
#include <scene\Component.h>
#include <scene\Texture.h>
#include <vector>
class MultipleTexture : public pm::Component
{
public:
	// Create component with multiple textures
	// Not recommended. Rather create textureAtlas.
	MultipleTexture();
	~MultipleTexture();
	void AddTexture(pm::Texture* texture);
	void SetTextureVector(std::vector<pm::Texture*> textures);
	std::vector<pm::Texture*> textures;
};

