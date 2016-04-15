#pragma once
#include <SDL.h>
#include <utility>
#include <vector>
using namespace std;
class Physics
{
public:
	static void printRect(const SDL_Rect& r);
	static void printA(const vector<vector<SDL_Rect>>& r);
	Physics();
	~Physics();
	static bool checkCollision(const SDL_Rect &entity, const SDL_Rect &envirnomnet);
	static bool isIntersect( pair<int,int> l, pair<int,int> h );
	static bool checkCollision(const vector< vector<SDL_Rect> > &map, const SDL_Rect &pos);
	static pair<int, int> getCellPosition( const SDL_Rect &pos ,int tileSizeDest );
	static bool isSameOrIn(pair<int, int> l, pair<int, int> h);
	static bool isSameOrIn(const SDL_Rect &map, const SDL_Rect &cam);
};

