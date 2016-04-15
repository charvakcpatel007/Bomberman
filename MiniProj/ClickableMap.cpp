#include "ClickableMap.h"
#include "MouseHandler.h"
#include <cstdio>

ClickableMap::ClickableMap()
{
	highLightThickness = 5;
	isBombermanPresent = 0;
}

void ClickableMap::draw()
{
	const int &ts = tileSizeDest;

	for (int i = 0; i < mapData.size(); i++)
	{

		for (int j = 0; j < mapData[i].size(); j++)
		{
			int code = mapData[i][j];
			pos = { j * ts + drawOffsetPtr->first, i * ts + drawOffsetPtr->second, ts, ts };
			if ( code == BOMBERMAN )
			{
				src = tileSrc[OPEN];
				SDL_RenderCopy(renderer, image, &src, &pos);
				SDL_RenderCopy(renderer, bomberman.image, &bomberman.src, &pos);
			}
			else if ( code == ENEMY )
			{
				src = tileSrc[OPEN];
				SDL_RenderCopy(renderer, image, &src, &pos);
				SDL_RenderCopy(renderer, enemy.image, &enemy.src, &pos);
			}
			else
			{
				src = tileSrc[code];
				SDL_RenderCopy(renderer, image, &src, &pos);
			}

		}
	}
	highLightCurTile();
}


void ClickableMap::update()
{
	setCurTile();
	processClick();
	processHotkeyPress();
}

void ClickableMap::processClick()
{
	int diff = 0;
	if ( isMousePressed == 1 )
	{
		diff = 1;
		isMousePressed = 0;
	}
	else
	{
		return;
	}
	if (curTile.first == 0 || curTile.first == mapData.size() - 1 )
	{
		return;
	}
	if (curTile.second == 0 || curTile.second == mapData[ 0 ].size() - 1)
	{
		return;
	}
	int &curData = mapData[curTile.first][curTile.second];
	curData = curData + diff;
	if (curData == -1)curData = 4;
	if (curData == 5)curData = 0;
	if ( isBombermanPresent )
	{
		if (curData == BOMBERMAN)curData++;
		else if (curData == BOMBERMAN + 1)isBombermanPresent = false;

	}
	else
	{
		if (curData == BOMBERMAN)isBombermanPresent = true;

	}
}

void ClickableMap::processDrag()
{

}

ClickableMap::~ClickableMap()
{
}


void ClickableMap::processHotkeyPress()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	int preState = mapData[curTile.first][curTile.second];
	cout << isBombermanPresent << endl;
	if (curTile.first == 0 || curTile.first == mapData.size() - 1)
	{
		return;
	}
	if (curTile.second == 0 || curTile.second == mapData[0].size() - 1)
	{
		return;
	}
	if (currentKeyStates[SDL_SCANCODE_1])
	{
		mapData[curTile.first][curTile.second] = OPEN;
		if (preState == BOMBERMAN)isBombermanPresent = false;
	}
	else if (currentKeyStates[SDL_SCANCODE_2])
	{
		mapData[curTile.first][curTile.second] = BRICK;
		if (preState == BOMBERMAN)isBombermanPresent = false;
	}
	else if (currentKeyStates[SDL_SCANCODE_3])
	{
		mapData[curTile.first][curTile.second] = BLOCK;
		if (preState == BOMBERMAN)isBombermanPresent = false;
	}
	else if (currentKeyStates[SDL_SCANCODE_4])
	{
		if ( !isBombermanPresent )
		{
			mapData[curTile.first][curTile.second] = BOMBERMAN;
			isBombermanPresent = true;
		}
			
	}
	else if (currentKeyStates[SDL_SCANCODE_5])
	{
		mapData[curTile.first][curTile.second] = ENEMY;
		if (preState == BOMBERMAN)isBombermanPresent = false;
	}
}

void ClickableMap::setImage(const char* path)
{
	Image::setImage(path);
	addCharImages();
}

void ClickableMap::setCurTile()
{
	pair<int, int> curMpos = MouseHandler::getMousePosition();
	int row = (curMpos.second - drawOffsetPtr->second) / tileSizeDest;
	int coloumn = ( curMpos.first - drawOffsetPtr->first ) / tileSizeDest;
	if ( !(row  + 1 > mapData.size() || coloumn  + 1 > mapData[ 0 ].size() ) && ( row >= 0 && coloumn >= 0 ) )
	{
		curTile.first = row;
		curTile.second = coloumn;
	}
	
}

void ClickableMap::highLightCurTile()
{
	SDL_Rect drawRect = { curTile.second * tileSizeDest + drawOffsetPtr->first, curTile.first * tileSizeDest + drawOffsetPtr->second, tileSizeDest, tileSizeDest };
	SDL_SetRenderDrawColor(renderer, 0, 0, 250, 1);
	for (int i = 0; i < highLightThickness; i++)
	{
		drawRect.x--;
		drawRect.y--;
		drawRect.w += 2;
		drawRect.h += 2;
		SDL_RenderDrawRect(renderer, &drawRect);
	}
	

}

void ClickableMap::addCharImages()
{
	bomberman.setRenderer(renderer);
	bomberman.setImage("res//george.png");
	bomberman.src = { 0, 0, 48, 48 };

	enemy.setRenderer(renderer);
	enemy.setImage("res//spritesheetBalloon.png");
	enemy.src = { 0, 0, 76, 121 };
}

void ClickableMap::expandRow()
{
	int n = mapData[0].size();
	mapData.push_back( vector<int>(n , BLOCK ) );
}

void ClickableMap::expandColoumn()
{
	for (int i = 0; i < mapData.size(); i++ )
	{
		mapData[i].push_back(BLOCK);
	}
}

void ClickableMap::contractRow()
{
	mapData.pop_back();
	vector<int> &temp = mapData.back();
	for (int i = 0; i < temp.size(); i++ )
	{
		temp[i] = BLOCK;
	}
}

void ClickableMap::contractColoumn()
{
	for (int i = 0; i < mapData.size(); i++)
	{
		mapData[i].pop_back();
		mapData[ i ].back() = BLOCK;
	}
}
