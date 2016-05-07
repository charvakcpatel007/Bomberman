#pragma once
#include "Scene.h"
#include "EnemyColletion.h"
#include "Bomberman.h"
#include "Bomb.h"

enum MapShowState
{
	GAME_RUNNING,
	GAME_SUCCESS,
	GAME_OVER
};

class MapShowScene :
	public Scene
{
public:
	virtual void init(SDL_Window* w, SDL_Surface* s, SDL_Renderer* r, int tileSizeDest, pair<int,int> d, Map *map, TTF_Font* gF);
	virtual void update() override;
	virtual void render() override;
	virtual void updateOffset() override;

	Bomberman bomberman;
	EnemyColletion enemies;
	void checkEnemies_Bomberman();
	void checkBomb_Char();
	Bomb *bomb;
	Map *curMap;
	MapShowScene();
	void putBomb();
	~MapShowScene();
	MapShowState mapShowState;
	TextSprite statusString;
	int s_timeLeft;
	int timeLeft;
};

