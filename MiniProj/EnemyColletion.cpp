#include "EnemyColletion.h"
#include "MapShowScene.h"


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
	e.init( mms );
	e.drawOffsetPtr = drawOffsetPtr;

}

void EnemyColletion::init(MapShowScene* m)
{
	mms = m;
	vector< vector<int> > mapData = mms->curMap->mapData;
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
	for (auto itr = enemyList.begin(); itr != enemyList.end(); itr++)
	{
		if (itr->isDead)continue;
		itr->update();
	}
}

void EnemyColletion::draw()
{
	for (auto itr = enemyList.begin(); itr != enemyList.end(); itr++)
	{
		if (itr->isDead)continue;
		itr->draw();
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


