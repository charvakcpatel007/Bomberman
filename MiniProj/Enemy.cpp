#include "Enemy.h"
#include "Physics.h"
#include <ctime>
#include <SDL.h>


Enemy::Enemy()
{
	setDefaultSrcRect();
}

void Enemy::init(Map* m)
{
	map = m;
	srcTileX = 76;
	srcTileY = 121;
	int newHeight = 100;
	noOfFrames = 11;
	startTime = time(0);
	duration = 300;
	srcFrameRects.push_back(vector< SDL_Rect>( noOfFrames ));
	for (int i = 0; i < noOfFrames; i++ )
	{
		srcFrameRects[0][i] = { 0, i * srcTileY, newHeight, newHeight };
	}
	turnChance = 50;
	rate = 2.0f;
	curPosition = 0;
	isPlaying = false;
	moveSpeed = 2;
	collideroffset = 15;
	magnificationOffset = 17;
	direction = make_pair(0 , 1);
	pos.x = startC * tileSizeDest;
	pos.y = startR * tileSizeDest;
	pos.x += collideroffset;
	pos.y += collideroffset;
	pos.w = tileSizeDest - collideroffset * 2;
	pos.h = tileSizeDest - collideroffset * 2;
}

void Enemy::turnRandom()
{
	pair<int,int> cellPos = Physics::getCellPosition(pos, tileSizeDest);
	
	int num_random = 1+ rand() % 100;
	
	if ( SDL_GetTicks() - startTime < duration )
	{
		return;
	}
	
	if ( num_random > turnChance )//50% chance that it is gonna turn
	{
		num_random = 1 + rand() % 100;//50% chance that it will turn left, rest for right
		if ( num_random <= turnChance )
		{
			int nextX, nextY;
			pair<int, int> nextDir = getLeft();
			nextX = pos.x + tileSizeDest * nextDir.first;
			nextY = pos.y + tileSizeDest * nextDir.second;
			SDL_Rect nextPos = pos;
			nextPos.x = nextX;
			nextPos.y = nextY;
			if (!Physics::checkCollision(map->mapCollider, nextPos))
			{
				direction = nextDir;
			}
		}
		else
		{
			int nextX, nextY;
			pair<int, int> nextDir = getLeft();
			nextX = pos.x + tileSizeDest * nextDir.first;
			nextY = pos.y + tileSizeDest * nextDir.second;
			SDL_Rect nextPos = pos;
			nextPos.x = nextX;
			nextPos.y = nextY;
			if (!Physics::checkCollision(map->mapCollider, nextPos))
			{
				direction = nextDir;
			}
		}
	}
	startTime = SDL_GetTicks();
}



void Enemy::update()
{
	Animation::update();
	SDL_Rect previousState = pos;
	
	pos.x += moveSpeed * direction.first;
	pos.y += moveSpeed * direction.second;

	if (Physics::checkCollision(map->mapCollider, pos))
	{
		pos = previousState;
		direction.first = -direction.first;
		direction.second = -direction.second;
	}

	turnRandom();
	
}

void Enemy::setDefaultSrcRect()
{
	src = { 0, 0, 76, 121 };
}


Enemy::~Enemy()
{
}

pair<int,int> Enemy::getLeft()
{
	pair<int, int> ret;
	if ( direction.first == 1 && direction.second == 0 )
	{
		ret = make_pair( 0, -1 );
	}
	else if (direction.first == -1 && direction.second == 0 )
	{
		ret = make_pair(0, 1 );
	}
	else if (direction.first == 0 && direction.second == -1 )
	{
		ret = make_pair(-1, 0);
	}
	else if (direction.first == 0 && direction.second == 1 )
	{
		ret = make_pair(1, 0);
	}
	return ret;
}

pair<int,int> Enemy::getRight()
{
	pair<int, int> ret;
	if (direction.first == 1 && direction.second == 0)
	{
		ret = make_pair(0, 1);
	}
	else if (direction.first == -1 && direction.second == 0)
	{
		ret = make_pair(0, -1);
	}
	else if (direction.first == 0 && direction.second == -1)
	{
		ret = make_pair(1, 0);
	}
	else if (direction.first == 0 && direction.second == 1)
	{
		ret = make_pair(-1, 0);
	}
	return ret;
}
