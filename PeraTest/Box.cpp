#include "Box.h"
#include <graphics\Color.h>
#include <graphics\Drawable.h>
#include <scene\Texture.h>
#include <graphics\SpriteBatch.h>
#include <core\Passert.h>

#define Resources pm::ResourceManager::GetInstance()
#define SB pm::SpriteBatch::GetInstance()

Box::Box()
{
	entity = new pm::GameEntity;
	entity->AddComponent(new pm::Color(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));
	entity->AddComponent(new pm::Rectangle(WIDTH, HEIGHT));
	//entity->GetComponent<Rectangle>()->SetOrigin(WIDTH * 0.5f, HEIGHT * 0.5f);
	entity->AddComponent(new pm::Drawable);
	entity->AddComponent(new pm::Transformable);
	entity->AddComponent(new pm::Texture("BOX.png"));
}

Box::~Box()
{
	delete entity;
}

void Box::Draw()
{
	SB->AddGameEntity(entity, false);
}

pm::Transformable* Box::Transform()
{
	pm::Transformable* transform = entity->GetComponent<pm::Transformable>();
	ASSERT_NEQUAL(transform, nullptr);
	return transform;
}

pm::Rectangle* Box::Rectangle()
{
	pm::Rectangle* rectangle = entity->GetComponent<pm::Rectangle>();
	ASSERT_NEQUAL(rectangle, nullptr);
	return rectangle;
}

void Box::ChangeTexture(std::string name)
{
	entity->AddComponent(new pm::Texture(name));
}

bool Box::Contains(glm::vec2 coordinate)
{
	glm::vec2 size = Rectangle()->GetSize();
	glm::vec2 location = Transform()->GetPosition();

	if (coordinate.x >= location.x && coordinate.x <= location.x + size.x &&
		coordinate.y >= location.y && coordinate.y <= location.y + size.y)
		return true;

	return false;
}