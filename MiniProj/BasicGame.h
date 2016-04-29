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
#include <SDL_ttf.h>
#include "MouseHandler.h"

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

	void run();
	void gameLoop();
	virtual void processInput() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	GameState gameState;
	bool isClicked();
protected:
	SDL_Window* window;
	SDL_Surface* windowSurface;
	SDL_Event* evnt;
	
	Timer fpsTimer;
	float fps;
	int desiredfps;
	float desiredTime;
	bool vsync;
	SDL_Renderer* renderer;
	int tileSizeDest;
	pair<int, int> dimension;// width hight
	TTF_Font* gFont;
	bool isFullScreen;
	bool isCamInLimit(pair<int, int> drawOffset, Map& curMap); 
	pair<int, int> mouseClickData;
	
};

