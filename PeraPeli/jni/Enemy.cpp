#include "Enemy.h"

#include "MultipleTexture.h"

Enemy::Enemy() :SpriteObject()
{
	done = false;
	timer = 0;
	AddComponent(NEW MultipleTexture());
	currentTexture = nullptr;
	justCreated = true;
}


Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{
	timer += deltaTime;
	if (justCreated)
	{
		if (timer > 300000000.0f)
		{
			justCreated = false;
			SetDrawState(true);
		}
		return;
	}
	if (timer > 50000000.0f)
	{
		UpdateTextureIndex();
		ChangeCurrentTexture();
		timer = 0;
	}
}

void Enemy::ChangeCurrentTexture()
{
	if (currentTexture != nullptr)
	{
		AddComponent(currentTexture);
		//pm::Texture* texture = GetComponent<pm::Texture>();
		//*texture = *currentTexture;
	}
}

void Enemy::UpdateTextureIndex()
{
	if (currentTexture == nullptr)
		return;
	MultipleTexture* mTexture = GetComponent<MultipleTexture>();
	if (currentTexture == mTexture->textures[mTexture->textures.size() - 1])
	currentTexture = mTexture->textures[0];
	else
	{
		for (int i = 0; i < mTexture->textures.size(); i++)
		{
			if (mTexture->textures[i] == currentTexture)
			{
				currentTexture = mTexture->textures[i + 1];
				return;
			}
			
		}
	}
	
}

void Enemy::AddTexture(pm::Texture* texture)
{
	MultipleTexture* mTexture = GetComponent<MultipleTexture>();
	mTexture->AddTexture(texture);

	if (currentTexture != nullptr)
		currentTexture = texture;
}

void Enemy::SetTextureVector(std::vector<pm::Texture*> textures)
{
	if (textures.size() == 0)
		return;
	currentTexture = textures[0];
	MultipleTexture* mTexture = GetComponent<MultipleTexture>();

	mTexture->SetTextureVector(textures);

	// Check if Texture-component has been created, if not
	// Create memorylocation for new Texture
	if (GetComponent<pm::Texture>() == nullptr)
	{
		AddComponent(textures[0]);
	}
}