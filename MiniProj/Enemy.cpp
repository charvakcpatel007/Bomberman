#include "Enemy.h"


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
	
	moveSpeed = 3;
	collideroffset = 15;
	pos.x = collideroffset + 10;
	pos.y = collideroffset + 10;
	pos.w = tileSizeDest - collideroffset * 2;
	pos.h = tileSizeDest - collideroffset * 2;
	isPlaying = true;
	magnificationOffset = 21;
}

void Enemy::update()
{
	Animation::update();
}

Enemy::~Enemy()
{
}
