#pragma once
#include "Enemy.h"
#include <list>

class EnemyColletion
{
public:
	EnemyColletion();
	list<Enemy> enemyList;
	void init( MapShowScene *m );
	void update();
	void draw();
	virtual ~EnemyColletion();
	int tileSizeDest;
	void setImage(const char* path);
	void setRenderer(SDL_Renderer* r);
	SDL_Renderer* renderer;
	const char* imagePath;
	pair<int, int> *drawOffsetPtr;
	MapShowScene* mms;
private:
	void addEnemy( int row, int coloumn );
};

