#include "BasicGame.h"


BasicGame::BasicGame()
{
	srand(time(0));
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	isFullScreen = false;
	TTF_Init();
	gFont = TTF_OpenFont("res//comicbd.ttf", 70);
	dimension = make_pair(1000, 600);
	window = SDL_CreateWindow("MP3", 20, 30, dimension.first, dimension.second, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	vsync = true;
	evnt = new SDL_Event();
	fpsTimer.start();
	desiredfps = 60;
	desiredTime = 1000.0f / desiredfps;
	gameState = GameState::PLAY;
	mouseClickData = make_pair(0, 0);
}


BasicGame::~BasicGame()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void BasicGame::run()
{
	gameLoop();
}

bool BasicGame::isCamInLimit(pair<int, int> drawOffset, Map& curMap)
{

	SDL_Rect camRect = { -drawOffset.first, -drawOffset.second, dimension.first, dimension.second };

	SDL_Rect mapRect = { 0, 0, curMap.mapData[0].size() * tileSizeDest, curMap.mapData.size() * tileSizeDest };
	Physics::printRect(camRect); cout << endl;
	if (mapRect.w < camRect.w)mapRect.w = camRect.w;
	if (mapRect.h < camRect.h)mapRect.h = camRect.h;
	if (Physics::isSameOrIn(mapRect, camRect))
	{
		return true;
	}
	return false;
}

bool BasicGame::isClicked()
{
	if (mouseClickData.first == 0 && mouseClickData.second == 1)
	{
		return true;
	}
	return false;
}

void BasicGame::gameLoop()
{
	fpsTimer.stop();
	while (gameState != GameState::QUIT)
	{
		fpsTimer.start();
		processInput();
		mouseClickData.first = mouseClickData.second;
		mouseClickData.second = MouseHandler::isLeftDown();
		update();
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		render();
		SDL_RenderPresent(renderer);
		float x = desiredTime - fpsTimer.getTicks();
	}
}
