#include "Physics.h"
#include <iostream>

void printRect(const SDL_Rect &r)
{
	printf("( %d, %d, %d, %d )", r.x, r.y, r.w, r.h);
}

void printA(const vector< vector<SDL_Rect>> &r)
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
				cout << endl;
				return true;
			}
		}
	}
	return false;
}

Physics::~Physics()
{
}
