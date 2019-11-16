#pragma once
#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent *transform;
	SpriteComponent *sprite;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{

		if (Game::event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (sprite->previousAnimation == "IdleUp" ||
				sprite->previousAnimation == "WalkUp")
			{
				transform->velocity.Zero();
				sprite->Play("ShootUp");
				sprite->spriteFlip = SDL_FLIP_NONE;
				// fix repeating animation later
			}
			else if (sprite->previousAnimation == "IdleDown" ||
				sprite->previousAnimation == "WalkDown")
			{
				transform->velocity.Zero();
				sprite->Play("ShootDown");
				sprite->spriteFlip = SDL_FLIP_NONE;
				// fix repeating animation later
			}
			else if (sprite->previousAnimation == "IdleRight" ||
				sprite->previousAnimation == "WalkRight")
			{
				transform->velocity.Zero();
				sprite->Play("ShootRight");
				// fix repeating animation later
			}
		}

		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				sprite->Play("WalkUp");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->Play("WalkDown");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->Play("WalkRight");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->Play("WalkRight");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				sprite->Play("IdleUp");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				sprite->Play("IdleDown");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->Play("IdleRight");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->Play("IdleRight");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
			default:
				break;
			}
		}
	}
};