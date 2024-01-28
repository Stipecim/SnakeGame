#pragma once

#include "Game.h"
#include "SDL.h"
#include "TextureManager.h"

class Menu {
public:
	Menu() {

	};
	void SetMenu(const char* filepath) {
		playbutton = TextureManager::LoadTexture(filepath);
		if (playbutton == nullptr) {
			throw std::runtime_error("Failed to load texture from file: " + std::string(filepath));
		}
	
	}
	void Draw() {
		TextureManager::draw(playbutton, srcRect, buttonRect);
	}

	
	SDL_Rect srcRect = { 0, 0, 200, 100 };
	SDL_Rect buttonRect = {150, 360, 200, 100};

private:
	SDL_Texture* playbutton;
};