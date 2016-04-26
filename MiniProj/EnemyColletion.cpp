#include "EnemyColletion.h"


EnemyColletion::EnemyColletion()
{
}

void EnemyColletion::addEnemy(int row, int coloumn)
{
	enemyList.emplace_back();
	Enemy &e = enemyList.back();
	e.startC = coloumn;
	e.startR = row;
	e.tileSizeDest = tileSizeDest;
	e.setRenderer(renderer);
	e.setImage(imagePath);
	e.init( *map );
	e.drawOffsetPtr = drawOffsetPtr;

}

void EnemyColletion::init(Map& m)
{
	map = &m;
	vector< vector<int> > mapData = m.mapData;
	for (int i = 0; i < mapData.size(); i++ )
	{
		for (int j = 0; j < mapData[i].size(); j++ )
		{
			if (mapData[i][ j ] == Map::ENEMY )
			{
				addEnemy(i, j);
			}
		}
	}
}

void EnemyColletion::update()
{
	for (int i = 0; i < enemyList.size(); i++)
	{
		
		enemyList[i].update();
	}
}

void EnemyColletion::draw()
{
	for (int i = 0; i < enemyList.size(); i++ )
	{
		enemyList[i].draw();
	}
}

EnemyColletion::~EnemyColletion()
{
}

void EnemyColletion::setImage(const char* path)
{
	imagePath = path;
}

void EnemyColletion::setRenderer(SDL_Renderer* r)
{
	renderer = r;
}


