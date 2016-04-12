#include "BasicGame.h"


BasicGame::BasicGame()
{
	srand(time(0));
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	dimension = make_pair(1250, 680);
	window = SDL_CreateWindow("MP3", 20, 30, dimension.first, dimension.second, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	vsync = true;
	evnt = new SDL_Event();
	fpsTimer.start();
	desiredfps = 60;
	desiredTime = 1000.0f / desiredfps;
	gameState = GameState::PLAY;
}


BasicGame::~BasicGame()
{
}

void BasicGame::run()
{
	gameLoop();
}

void BasicGame::gameLoop()
{
	fpsTimer.stop();
	while (gameState != GameState::QUIT)
	{
		fpsTimer.start();
		processInput();
		update();
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		render();
		SDL_RenderPresent(renderer);
		float x = desiredTime - fpsTimer.getTicks();

	}
}
