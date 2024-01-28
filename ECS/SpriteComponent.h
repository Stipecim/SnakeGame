#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SDL.h"
#include "../TextureManager.h"


class SpriteComponent : public Component {
public:

	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTex(path);
	}
	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}
	void init() override {	
		
		transform = &entity->getComponent<TransformComponent>(); 

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		destRect.w = destRect.h = 32;
		
	}

	void update() override {
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}

	void draw() override {
		TextureManager::draw(texture, srcRect, destRect);
	}

	bool isInit() override {
		return true;
	}
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

};