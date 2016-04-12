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
#include "EnemyColletion.h"

enum GameState
{
	PLAY,
	PAUSE,
	MAINMENU,
	QUIT
};

class BasicGame
{
public:
	BasicGame();
	virtual ~BasicGame();
	virtual void updateOffset() = 0;

	void run();
	void gameLoop();
	virtual void processInput() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
protected:
	SDL_Window* window;
	SDL_Surface* windowSurface;
	SDL_Event* evnt;
	GameState gameState;
	Timer fpsTimer;
	float fps;
	int desiredfps;
	float desiredTime;
	bool vsync;
	SDL_Renderer* renderer;
	int tileSizeDest = 10;
	pair<int, int> drawOffset;
	pair<int, int> dimension;
};

