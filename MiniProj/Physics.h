#pragma once
#include <SDL.h>
#include <utility>
#include <vector>
using namespace std;
class Physics
{
public:
	Physics();
	~Physics();
	static bool checkCollision(const SDL_Rect &entity, const SDL_Rect &envirnomnet);
	static bool isIntersect( pair<int,int> l, pair<int,int> h );
	static bool checkCollision(const vector< vector<SDL_Rect> > &map, const SDL_Rect &pos);
};

