#include "MouseHandler.h"

using namespace std;



MouseHandler::MouseHandler()
{
}

std::pair<int, int> MouseHandler::getMousePosition()
{
	SDL_PumpEvents();
	pair<int, int> ret;
	SDL_GetMouseState(&ret.first, &ret.second);
	return ret;
}

bool MouseHandler::isLeftDown()
{
	SDL_PumpEvents();
	if( SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT) )
	{
		return true;
	}
	return false;
}

bool MouseHandler::isRightDown()
{
	SDL_PumpEvents();
	if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		return true;
	}
	return false;
}

SDL_Rect MouseHandler::getPositionRectangle()
{
	pair<int, int> pos = MouseHandler::getMousePosition();
	SDL_Rect ret = { pos.first, pos.second, 10, 10 };
	return ret;
}

MouseHandler::~MouseHandler()
{
}
