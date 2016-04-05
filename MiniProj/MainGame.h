#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include "Timer.h"
#include "Image.h"
#include <string>
#include "Animation.h"
#include "Bomberman.h"
#include "Map.h"
#include "FileHandler.h"
#include "Enemy.h"
using namespace std;

enum GameState
{
	PLAY,
	PAUSE,
	MAINMENU,
	QUIT
};

class MainGame
{
public:
	MainGame();
	~MainGame();
	void run();
	void loadRes();
	void gameLoop();
	void processInput();
	void update();
	void render();
	void loadMaps();
	SDL_Renderer* renderer;
	vector< Map > maps;
	int tileSizeDest = 10;

private:
	SDL_Window* window;
	SDL_Surface* windowSurface;
	SDL_Event* evnt;
	GameState gameState;
	Timer fpsTimer;
	float fps;
	int desiredfps;
	float desiredTime;
	bool vsync;
	Bomberman bomberman;
	Enemy e;
};

