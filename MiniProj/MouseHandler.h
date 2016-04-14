#pragma once
#include <SDL.h>
#include <utility>
using namespace std;
class MouseHandler
{
public:
	MouseHandler();
	static std::pair<int,int> getMousePosition();
	static bool isLeftDown();
	static bool isRightDown();
	static SDL_Rect getPositionRectangle();
	virtual ~MouseHandler();
private:
};

