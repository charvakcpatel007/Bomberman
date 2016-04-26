#pragma once
#include "Scene.h"
#include "EnemyColletion.h"
#include "Bomberman.h"

class MapShowScene :
	public Scene
{
public:
	virtual void init(SDL_Window* w, SDL_Surface* s, SDL_Renderer* r, int tileSizeDest, pair<int,int> d, Map &map);
	virtual void update() override;
	virtual void render() override;
	virtual void updateOffset() override;

	Bomberman bomberman;
	EnemyColletion enemies;
	void checkEnemies_Bomberman();
	Map *curMap;
	MapShowScene();
	~MapShowScene();
};

