#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

#define SPEED_LEVEL_EASY 1
#define MENU_STATE 0
#define GAME_STATE 1
#define PAUSE 2

class Game{
public:
	Game() {};
	~Game() {};


	void init(const char* title, int xpos, int ypos, int w, int h, bool is_fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running();

	static SDL_Renderer* renderer;

	static SDL_Event event;

	int getGameState() { return gameState; }

private:
	int gameState = MENU_STATE;
	int count = NULL;
	bool isRunning;
	SDL_Window* window;
	
};
