#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class Keyboard : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* snakeHead;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		snakeHead = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w: // up
				if (transform->velocity.x != 0 && !(transform->velocity.y < 0)) {
					transform->velocity.y = -32;
					transform->velocity.x = 0;
					snakeHead->setTex("assets/SnakeHead.png");
				}
				break;
			case SDLK_a: // left 
				if (transform->velocity.y != 0 && !(transform->velocity.x < 0)) {
					transform->velocity.x = -32;
					transform->velocity.y = 0;
					snakeHead->setTex("assets/snakeheadL.png");
				}
				break;
			case SDLK_s: // down
				if (transform->velocity.x != 0 && !(transform->velocity.y > 0)) {
					transform->velocity.y = 32;
					transform->velocity.x = 0;
					snakeHead->setTex("assets/snakeheadD.png");
				}
				break;
			case SDLK_d: // right
				if (transform->velocity.y != 0 && !(transform->velocity.x > 0)) {
					transform->velocity.x = 32;
					transform->velocity.y = 0;
					snakeHead->setTex("assets/snakeheadR.png");
				}
				break;
			default:
				break;
			}
		}
		/*if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			default:
				break;
			}
		}*/
	}
};