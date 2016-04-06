#include "Bomberman.h"
#include "MainGame.h"
#include <iostream>
#include <SDL.h>

Bomberman::Bomberman()
{
	isPlaying = false;
	magnificationOffset = 20;
}



void Bomberman::init( Map& m )
{
	map = &m;
	int startR = 0;
	int startC = 0;
	{
		vector< vector<int> > &d = m.mapData;
		for (int i = 0; i < d.size(); i++ )
		{
			for (int j = 0; j < d[i].size(); j++ )
			{
				if ( d[ i ][ j ] ==  Map::BOMBERMAN )
				{
					startR = i;
					startC = j;
				}
			}
		}
	}
	srcTileX = 48;
	srcTileY = 48;
	noOfFrames = 4;
	
	//Here tile is a Square so using srcTileX everywhere
	//Total type of stripes are 4
	for (int j = 0; j < 4; j++)
	{
		srcFrameRects.push_back(vector< SDL_Rect >());
		vector< SDL_Rect > &temp = srcFrameRects.back();

		//Frames are 4 per stripe
		for (int i = 0; i < noOfFrames; i++)
		{
			SDL_Rect t = { j * srcTileX, i * srcTileX, srcTileX, srcTileX };
			temp.push_back(t);
		}
	}
	
	
	strip = 2;
	rate = 2.0f;
	curPosition = 0;

	moveSpeed = 3;
	collideroffset = 13;
	pos.x = startC * tileSizeDest;
	pos.y = startR * tileSizeDest;
	pos.x += collideroffset;
	pos.y += collideroffset;
	pos.w = tileSizeDest - collideroffset * 2;
	pos.h = tileSizeDest - collideroffset * 2;
	
}

void Bomberman::update()
{
	SDL_Rect previousState = pos;
	const Uint8* curKeyStates = SDL_GetKeyboardState(NULL);
	if (curKeyStates[ SDL_SCANCODE_UP ] )
	{
		pos.y -= moveSpeed;
		strip = 2;
		isPlaying = true;
		Animation::update();
	}
	else if (curKeyStates[SDL_SCANCODE_DOWN])
	{
		pos.y += moveSpeed;
		strip = 0;
		isPlaying = true;
		Animation::update();
	}
	else if (curKeyStates[SDL_SCANCODE_LEFT])
	{
		pos.x -= moveSpeed;
		strip = 1;
		isPlaying = true;
		Animation::update();
	}
	else if (curKeyStates[SDL_SCANCODE_RIGHT])
	{
		pos.x += moveSpeed;
		strip = 3;
		isPlaying = true;
		Animation::update();
	}
	else
	{
		isPlaying = false;
	}
	
	if (Physics::checkCollision( map->mapCollider, pos ))
	{
		pos = previousState;
	}
}



Bomberman::~Bomberman()
{
}
