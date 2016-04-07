#include "Enemy.h"
#include "Physics.h"


Enemy::Enemy()
{
}

void Enemy::init(Map& m)
{
	map = &m;
	srcTileX = 76;
	srcTileY = 121;
	int newHeight = 100;
	noOfFrames = 11;

	srcFrameRects.push_back(vector< SDL_Rect>( noOfFrames ));
	for (int i = 0; i < noOfFrames; i++ )
	{
		srcFrameRects[0][i] = { 0, i * srcTileY, newHeight, newHeight };
	}

	rate = 2.0f;
	curPosition = 0;
	isPlaying = true;
	moveSpeed = 3;
	collideroffset = 15;
	magnificationOffset = 20;
	pos.x = startC * tileSizeDest;
	pos.y = startR * tileSizeDest;
	pos.x += collideroffset;
	pos.y += collideroffset;
	pos.w = tileSizeDest - collideroffset * 2;
	pos.h = tileSizeDest - collideroffset * 2;
}

void Enemy::update()
{
	
	Animation::update();
	SDL_Rect previousState = pos;
	if (Physics::checkCollision(map->mapCollider, pos))
	{
		pos = previousState;
	}
}


Enemy::~Enemy()
{
}
