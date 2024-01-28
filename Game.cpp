#include "Game.h"


#include "ECS/Components.h"

#include "Vector2D.h"
#include "Background.h"
#include "menu.h"

Menu menu;
Background background;
EntityManager manager;





SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

// Entities 
Entity& player(manager.addEntity());
Entity& food(manager.addEntity());


void Game::init(const char* title, int xpos, int ypos, int w, int h, bool is_fullscreen) {
	int FPS = 60;
	int flags = 0;
	if (is_fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "initialised" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, w, h, flags);
		if (window) {
			std::cout << "Window Created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer Created!" << std::endl;
		}

		isRunning = true;

	}
	background.SetBg("assets/Background.png");
	menu.SetMenu("assets/playbutton.png");

	// Snake
	player.setName("snake");
	player.addComponent<TransformComponent>();
	player.addComponent<SpriteComponent>("assets/SnakeHead.png");
	player.addComponent<Keyboard>();

	// Food
	food.setName("food");
	food.addComponent<TransformComponent>();
	food.addComponent<SpriteComponent>("assets/Food.png");
	
	//Borders

}
void Game::handleEvents() {
	
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT &&
			event.button.x >= menu.buttonRect.x &&
			event.button.x <= menu.buttonRect.x + menu.buttonRect.w &&
			event.button.y >= menu.buttonRect.y &&
			event.button.y <= menu.buttonRect.y + menu.buttonRect.h) 
		{
			menu.~menu();
			gameState = GAME_STATE;
			background.SetBg("assets/BackgroundGame.png");
			

		}
	default:
		break;
	}
}
void Game::update() {

	if (gameState == GAME_STATE) {
		manager.refresh();
		manager.update();

		//player.getComponent<TransformComponent>().position.Add(Vector2D(5, 0));
	}
}
void Game::render() {
	
	SDL_RenderClear(renderer);

	background.Draw();
	if (gameState == MENU_STATE) {
		menu.Draw();
	}
	else if (gameState == GAME_STATE) {
		manager.draw();
	}

	SDL_RenderPresent(renderer);
}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

bool Game::running() { return isRunning; };

