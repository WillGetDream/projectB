#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "../TextureManager.h"
#include <iostream>

class ColliderComponent : public Component
{
public:

	SDL_Rect collider;
	std::string tag;

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	TransformComponent* transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	ColliderComponent(std::string t, int posX, int posY, int colliderSize)
	{
		this->tag = t;
		this->collider.x = posX;
		this->collider.y = posY;
		this->collider.w = this->collider.h = colliderSize;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();
		
		// texture = TextureManager::LoadTexture("Assets/collider.png");

		srcRect = { 0,0,TILE_SIZE,TILE_SIZE };
		destRect = { collider.x,collider.y,collider.w,collider.h };
	}

	void update() override
	{
		if (tag != "terrain") // colliders associated with terrain won't have a transform component
		{
			if (tag == "player")
			{
				collider.x = static_cast<int>(transform->position.x + 16);
				collider.y = static_cast<int>(transform->position.y + 16);
				collider.w = TILE_SIZE;
				collider.h = TILE_SIZE;
			}
			else
			{
				collider.x = static_cast<int>(transform->position.x);
				collider.y = static_cast<int>(transform->position.y);
				collider.w = transform->width * transform->scale;
				collider.h = transform->height * transform->scale;
			}
		}

		// change this to commented code if using camera. See video # 21 @ 09:05
		// https://www.youtube.com/watch?v=rP62bS0k3nU&t=654s
		destRect.x = collider.x; // destRect.x = collider.x - Game::camera.x;
		destRect.y = collider.y; // destRect.y = collider.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};