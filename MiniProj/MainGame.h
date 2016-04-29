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
#include "BasicGame.h"
#include "MapShowScene.h"
#include "MainMenuScene.h"
#include "PauseMenuScene.h"
using namespace std;

class MainGame : public BasicGame
{
public:
	MainGame();
	~MainGame();
	void loadRes();

	void processInput();
	void update();
	void render();
	void loadMaps();
	
	Map *curMap;
	int curMapIndex;
	virtual void updateOffset();
	MapShowScene *mss;
	MainMenuScene mainMenu;
	PauseMenuScene pauseMenu;
	vector<string> mapNames;
	void loadMap(string &mapName);
	void transition_MainMenu_MapShow();
	void transition_MapShow_MainMenu();	
private:
	
};

