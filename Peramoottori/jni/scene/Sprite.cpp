#include "Sprite.h"
#include "core\Memory.h"
#include "scene\GameEntity.h"
#include "graphics\Drawable.h"
#include "graphics\Rectangle.h"
#include "scene\Transformable.h"
#include "graphics\Color.h"
#include "scene\Texture.h"
#include "scene\TextureCoordinates.h"

pm::Sprite::Sprite() : Component()
{
	fP = "noFilePath";
}

pm::Sprite::Sprite(std::string filePath) : Component()
{
	fP = filePath;
}

pm::Sprite::~Sprite()
{}

void pm::Sprite::SetParent(GameEntity* entity)
{
	parent = entity;

	parent->AddComponent(NEW Drawable());
	parent->AddComponent(NEW Rectangle());
	parent->AddComponent(NEW Transformable());
	parent->AddComponent(NEW Color());
	
	if (!strcmp(fP.c_str(), "noFilePath"))
	{
		Texture* tempTexture = NEW Texture(fP);
		parent->AddComponent(tempTexture);
		parent->AddComponent(NEW TextureCoordinates(0.0f, 0.0f, tempTexture->GetTrueSize().x, tempTexture->GetTrueSize().y));
	}
}