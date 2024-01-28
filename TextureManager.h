#pragma once

#include "Game.h"



class TextureManager {
public:

	static SDL_Texture* LoadTexture(const char* filelocation) {

		SDL_Surface* tempSurface = IMG_Load(filelocation);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
		SDL_FreeSurface(tempSurface);


		// Load head textures, Head up, head down

		return texture;
	}

	static void draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect) {
		SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
	}
};

