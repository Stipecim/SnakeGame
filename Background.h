#pragma once

#include "Game.h"
#include "SDL.h"
#include "TextureManager.h"

class Background {
public:
	Background() {
	
	};
	~Background() {
		SDL_DestroyTexture(bg);
	}
	void SetBg(const char* filepath) {
		bg = TextureManager::LoadTexture(filepath);
		if (bg == nullptr) {
			throw std::runtime_error("Failed to load texture from file: " + std::string(filepath));
		}
		srcRect.x = srcRect.y = 0;
		srcRect.w = 1280;
		srcRect.h = 768;
		destRect.w = 1280;
		destRect.h = 768;
	}
	void Draw(){
		TextureManager::draw(bg, srcRect, destRect);
	}
private:
	SDL_Texture* bg;
	SDL_Rect srcRect, destRect;
};