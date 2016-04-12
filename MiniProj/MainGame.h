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
	
	vector< Map > maps;
	void updateOffset();
private:
	Bomberman bomberman;
	EnemyColletion enemies;
};

