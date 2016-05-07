#include "Map.h"
#include <cstdio>


Map::Map()
{

	tileSize = 32;
	{
		SDL_Rect r = { 2 * tileSize, 1 * tileSize, tileSize, tileSize };// Open Tile Image
		tileSrc.push_back(r);
	}
	{
		SDL_Rect r = { 0 * tileSize, 1 * tileSize, tileSize, tileSize };// Brick Tile Image
		tileSrc.push_back(r);
	}
	{
		SDL_Rect r = { 5 * tileSize, 2 * tileSize, tileSize, tileSize };//Block TIle Images
		tileSrc.push_back(r);
	}
}

void Map::setUpCollider()
{
	int ts = tileSizeDest;

	for (int i = 0; i < mapData.size(); i++)
	{
		mapCollider.push_back( vector<SDL_Rect>() );
		for (int j = 0; j < mapData[i].size(); j++)
		{
			int code = mapData[i][j];

			SDL_Rect temp = { j * ts, i * ts, ts, ts };
			if (code == OPEN || code == BOMBERMAN || code == ENEMY)
			{
				temp.w = 0;
				temp.h = 0;
			}
			mapCollider[ i ].push_back(temp);
		}
	}
	//printA( mapCollider );
}


void Map::destoryTile(int row, int coloumn)
{
	if (mapData[row][coloumn] == BRICK )
	{
		mapData[row][coloumn] = OPEN;
		mapCollider[row][coloumn].w = mapCollider[row][coloumn].h = 0;
	}
} 

void Map::draw()
{
	const int &ts = tileSizeDest;
	
	for (int i = 0; i < mapData.size(); i++)
	{
		
		for (int j = 0; j < mapData[i].size(); j++)
		{
			int code = mapData[i][j];
			code = code == BOMBERMAN || code == ENEMY ? OPEN : code;
			src = tileSrc[ code ];
			pos = { j * ts + drawOffsetPtr->first,  i * ts + drawOffsetPtr->second, ts, ts };
			//SDL_Rect temp = mapCollider[i][j];
			//cout << temp.x << " " << temp.y << " " << temp.w << " "  <<  temp.h << endl;

			//draw fucntion is of parent class which draws according to the current
			//src and pos
			//In order to draw the whole map, for each code in mapData we are just changing the src and pos
			//Image::draw();
			//SDL_RenderCopy(renderer, image, &src, &pos);
			SDL_RenderCopy(renderer, image, &src, &pos);
			//SDL_RenderDrawRect(renderer, &mapCollider[ i ][ j ]);
			
		}
	}
}

Map::~Map()
{
}
