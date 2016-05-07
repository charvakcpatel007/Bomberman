#include "Physics.h"
#include <iostream>

void Physics::printRect(const SDL_Rect& r)
{
	printf("( %d, %d, %d, %d )", r.x, r.y, r.w, r.h);
}

void Physics::printA(const vector< vector<SDL_Rect>> &r)
{
	for (int i = 0; i < r.size(); i++)
	{
		for (int j = 0; j < r[i].size(); j++)
		{
			printRect(r[i][j]);
			cout << endl;
		}
		cout << endl;
	}
}

Physics::Physics()
{
}

bool Physics::checkCollision(const SDL_Rect &entity, const SDL_Rect &envirnomnet )
{
	if (envirnomnet.w == 0)
	{
		return false;
	}
	
	pair<int, int> x1 = make_pair( entity.x, entity.x + entity.w );
	pair<int, int> x2 = make_pair( envirnomnet.x, envirnomnet.x + envirnomnet.w);
	
	pair<int, int> y1 = make_pair(entity.y, entity.y + entity.h );
	pair<int, int> y2 = make_pair(envirnomnet.y, envirnomnet.y + envirnomnet.h);
	
	bool o1 = isIntersect(x1,x2);
	bool o2 = isIntersect(y1,y2);

	if (o2 && o1)return true;
	return false;
}

bool Physics::isIntersect(pair<int, int> l, pair<int, int> h)
{
	if (l.second < h.first || l.first > h.second)
		return false;
	return true;
}

bool Physics::checkCollision(const vector<vector<SDL_Rect>>& map, const SDL_Rect& pos)
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j].w == 0)continue;
			if (Physics::checkCollision(pos, map[i][j]))
			{
				return true;
			}
		}
	}
	return false;
}

bool Physics::checkCollision(const vector<SDL_Rect>& map, const SDL_Rect& pos)
{
	for (int i = 0; i < map.size(); i++)
	{
		if (map[i].w == 0)continue;
		if (Physics::checkCollision(pos, map[i]))
		{
			return true;
		}
	
	}
	return false;
}

bool Physics::checkCollision(const vector<vector<SDL_Rect*>>& map, const SDL_Rect& pos)
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j]->w == 0)continue;
			if (Physics::checkCollision(pos, *map[i][j]))
			{
				return true;
			}
		}
	}
	return false;
}

pair<int, int> Physics::getCellPosition( const SDL_Rect &pos, int tileSizeDest)//First -> X, Second-> Y
{
	int posX = pos.x + pos.w / 2;
	int posY = pos.y + pos.h / 2;
	pair<int, int> ret;
	ret.first = posX / tileSizeDest;
	ret.second = posY / tileSizeDest;
	return ret;
}

bool Physics::isSameOrIn(pair<int, int> l, pair<int, int> h)
{
	if ( l == h )
	{
		return true;
	}
	if ( l.first <= h.first && l.second >= h.second )
	{
		return true;
	}
	return false;
}

bool Physics::isSameOrIn(const SDL_Rect& map, const SDL_Rect& cam)
{
	pair<int, int> x1 = make_pair(map.x, map.x + map.w);
	pair<int, int> x2 = make_pair(cam.x, cam.x + cam.w);

	pair<int, int> y1 = make_pair(map.y, map.y + map.h);
	pair<int, int> y2 = make_pair(cam.y, cam.y + cam.h);

	bool o1 = isSameOrIn(x1, x2);
	bool o2 = isSameOrIn(y1, y2);

	if (o2 && o1)return true;
	return false;
}

Physics::~Physics()
{
}
