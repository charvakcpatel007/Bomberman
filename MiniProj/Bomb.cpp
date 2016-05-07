#include "Bomb.h"
#include "MapShowScene.h"
#include "Map.h"


Bomb::Bomb()
{
	bombState = BombState::INIT;
	blowTimeLeft = 2000;
	totalBlastTime = 400;
	curAlpha = 0.0f;
	l = r = t = b = 0;
}

pair<int, int> Bomb::getReach(vector<vector<int>>& mapData, int r, int c, int rdiff, int cdiff)
{
	const int OPEN = mms->curMap->OPEN;
	const int BRICK = mms->curMap->BRICK;
	const int BLOCK = mms->curMap->BLOCK;
	int cnt = radius;
	while (cnt--)
	{
		switch (mapData[r][c])
		{
		case OPEN:
			break;
		case BRICK:
			return make_pair(r, c);
			break;
		case BLOCK:
			r -= rdiff;
			c -= cdiff;
			return make_pair(r, c);
			break;
		}
		r += rdiff;
		c += cdiff;
	}
	r -= rdiff;
	c -= cdiff;
	return make_pair(r, c);
}

void Bomb::setLRUB()
{
	vector<vector<int> > &mapData = mms->curMap->mapData;
	//xy cell
	pair<int, int> cellPos = Physics::getCellPosition(pos, tileSizeDest);
	int r = cellPos.second;
	int c = cellPos.first;
	pair<int, int> ret;
	//Left
	ret = getReach( mapData, r, c - 1, 0, -1 );
	this->l = ret.second;
	//Right
	ret = getReach( mapData, r, c + 1, 0, 1 );
	this->r = ret.second;
	//Top
	ret = getReach( mapData, r - 1, c, -1, 0 );
	cout << ret.first << " " << ret.second << endl;
	this->t = ret.first;
	//Bottom
	ret = getReach( mapData, r + 1, c, 1, 0 );
	this->b = ret.first;

	int offsetCollider = 10;
	for (int itr = this->l; itr <= this->r; itr++ )
	{
		if (mapData[r][itr] == Map::BRICK)
		{
			mms->curMap->destoryTile(r, itr);
		}
		SDL_Rect temp = { itr * tileSizeDest + offsetCollider,  r * tileSizeDest + offsetCollider ,tileSizeDest - offsetCollider * 2, tileSizeDest - offsetCollider * 2 };
		blastCollider.push_back(temp);
	}
	cout << endl;
	for (int itr = this->t; itr <= this->b; itr++ )
	{
		if (mapData[itr][c] == Map::BRICK)
		{
			mms->curMap->destoryTile(itr, c);
		}
		SDL_Rect temp = { c * tileSizeDest + offsetCollider, itr * tileSizeDest + offsetCollider, tileSizeDest, tileSizeDest - offsetCollider * 2 };
		blastCollider.push_back(temp);
	}
}

void Bomb::init( MapShowScene* m )
{
	//67*70
	mms = m;
	heightSrc = 68;
	widthSrc = 67;
	src = { 0, 0, widthSrc, heightSrc };
	srcs.push_back( src );
	src = { heightSrc, 0, widthSrc, heightSrc};
	srcs.push_back( src );
	radius = 2;
	pos = { 0, 0, tileSizeDest, tileSizeDest };
	s_blowTimeLeft = SDL_GetTicks();
	s_totalBlastTime = SDL_GetTicks();
}

void Bomb::update()
{
	switch ( bombState )
	{
	case BombState::INIT:
		if (SDL_GetTicks() - s_blowTimeLeft > blowTimeLeft)
		{
			bombState = BombState::BLASTING;
			setLRUB();
			s_totalBlastTime = SDL_GetTicks();
		}
		break;
	case BombState::BLASTING:
		if ( SDL_GetTicks() - s_totalBlastTime > totalBlastTime )
		{
			bombState = BombState::DESTROYED;
		}
		break;
	case BombState::DESTROYED:
		break;
	}
}

void Bomb::drawForGivenPos(const SDL_Rect& curpos)
{
	SDL_Rect temp = curpos;
	temp.x += drawOffsetPtr->first;
	temp.y += drawOffsetPtr->second;
	SDL_RenderCopy(renderer, image, &src, &temp);
}



void Bomb::draw()
{
	int curTime = SDL_GetTicks() - s_totalBlastTime;
	pair<int, int> ret;
	switch (bombState)
	{
	case BombState::INIT:
		src = srcs[0];
		drawForGivenPos(pos);
		break;
	case BombState::BLASTING:
		
		if ( curTime < totalBlastTime / 2 )
		{
			SDL_SetTextureAlphaMod(image, 2 * (curTime) * (double)255.0 / totalBlastTime);
		}
		else
		{
			curTime -= totalBlastTime / 2;
			SDL_SetTextureAlphaMod(image, 255 * (1 - ( (float)curTime * 2 / totalBlastTime )));
		}
		
		src = srcs[1];
		//Horizontal
		
		ret = Physics::getCellPosition(pos, tileSizeDest);
		for (int i = l; i <= r; i++)
		{
			SDL_Rect curDraw = pos;
			curDraw.x = i * tileSizeDest;
			curDraw.y = ret.second * tileSizeDest;
			drawForGivenPos(curDraw);
		}
		//Vertical
		for (int i = t; i <= b; i++)
		{
			SDL_Rect curDraw = pos;
			curDraw.x = ret.first * tileSizeDest;
			curDraw.y = i * tileSizeDest;
			drawForGivenPos(curDraw);
		}
		break;
	case BombState::DESTROYED:
		break;
	}
}

BombCharStatus Bomb::getInteraction(GenericCharacter &character)
{
	const SDL_Rect &charcol = character.pos;
	switch (bombState)
	{
	case BombState::INIT:
		if ( Physics::checkCollision( charcol, this->pos ) )
		{
			return BombCharStatus::COLLISION;
		}
		break;
	case BombState::BLASTING:
		if (Physics::checkCollision( blastCollider, charcol))
		{
			return BombCharStatus::DESTORY;
		}
		break;
	case BombState::DESTROYED:
		return BombCharStatus::NOTHING;
		break;
	}
	return BombCharStatus::NOTHING;
}

Bomb::~Bomb()
{
}

