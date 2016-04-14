#include "Bomberman.h"
#include "MainGame.h"
#include <iostream>
#include <SDL.h>

Bomberman::Bomberman()
{
	isPlaying = false;
	magnificationOffset = 20;
	Bomberman::setDefaultSrcRect();
}

pair<int, int> Bomberman::getPositionFromMap()
{
	pair<int, int> p;
	vector< vector<int> > &d = map->mapData;
	for (int i = 0; i < d.size(); i++)
	{
		for (int j = 0; j < d[i].size(); j++)
		{
			if (d[i][j] == Map::BOMBERMAN)
			{
				p.first = i;//First is for Row
				p.second = j;//Second is for coloumn
			}
		}
	}
	return p;
}

void Bomberman::init( Map& m )
{
	map = &m;
	pair<int,int> p = getPositionFromMap();
	int startR = p.first;
	int startC = p.second;
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
	collideroffset = 15;
	magnificationOffset = 20;
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

void Bomberman::draw()
{
	SDL_Rect intermediatepos = pos;
	intermediatepos.x = screenDimension.first / 2;
	intermediatepos.y = screenDimension.second / 2;
	intermediatepos.x -= magnificationOffset;
	intermediatepos.y -= magnificationOffset;
	intermediatepos.h += magnificationOffset * 2;
	intermediatepos.w += magnificationOffset * 2;
	SDL_RenderCopy(renderer, image, isPlaying ? &srcFrameRects[strip][getCurFrame()] : &srcFrameRects[strip][0], &intermediatepos);
}

void Bomberman::setDefaultSrcRect()
{
	src = { 0, 0, 48, 48 };
}

Bomberman::~Bomberman()
{
}


