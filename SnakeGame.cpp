#include "Game.h"


 


/*	You know where to start now, everything is set set up, remember how snake moves using manager class 
	you will remember 
*/

// playbox will be able to fit 320 objects into scene window of width 640 - heigth 512 ; 
// problems to solve later on: 
	// - snake is moving on 1 fps by 32 pxels, speed is good but key delay is off way off , longer I wait worser I need to figure out input that matches
	//   fps time
	// - snake and food position in border box also add collision to borders of playbox in which will imediatly send you to main menu
	// - Rindomize food position in playbox
	// - Make sure that snake is 32px in size so that matches borders when full 
	// - snake body and tail draw 


Game* game = nullptr;

int main(int argc, char* agrv[]) {

	/*SDL_Init(SDL_INIT_EVERYTHING);  INITIALIZING SUBSYSTEMS // adutio, video etc.. 
	SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN); Creates window
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0); Renders inside windows 

	SDL_SetRenderDrawColor(renderer, 0, 111,0, 111); renders background color

	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);

	SDL_Delay(3000); */
	const int FPS = 60;
	
	const int TargetFrameTime = 1000 / FPS;
	
	const int TimePerUpdate = 1000 / 30;

	Uint32 framestart;

	int frametime;

	game = new Game();
	
	game->init("SnakeGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 768, false);

	Uint32 previousTime = SDL_GetTicks();
	int lagTime = 0;

	while (game->running()) {

		Uint32 currentTime = SDL_GetTicks();
		Uint32 elapsedTime = currentTime - previousTime;

		previousTime = currentTime;
		lagTime += elapsedTime;
		
		framestart = SDL_GetTicks();

		game->handleEvents();

		while (lagTime >= TimePerUpdate) {
			game->update();
		}
		game->render();

		frametime = SDL_GetTicks() - framestart;

		
		Uint32 frameTime = SDL_GetTicks() - currentTime;
		if (frameTime < TargetFrameTime) {
			SDL_Delay(TargetFrameTime - frameTime);
		}
		
	}
	game->clean();
	delete game;

	return 0;
}