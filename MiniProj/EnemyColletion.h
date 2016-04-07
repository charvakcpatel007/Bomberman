#pragma once
#include "Enemy.h"
class EnemyColletion
{
public:
	EnemyColletion();
	vector<Enemy> enemyList;
	void init( Map &m );
	void update();
	void draw();
	virtual ~EnemyColletion();
	int tileSizeDest;
	void setImage(const char* path);
	void setRenderer(SDL_Renderer* r);
	SDL_Renderer* renderer;
	const char* imagePath;
	Map* map;
private:
	void addEnemy( int row, int coloumn );
};

