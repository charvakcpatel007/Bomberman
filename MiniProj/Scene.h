#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <utility>

class Scene
{
public:
	Scene();
	virtual void init(SDL_Window* w, SDL_Surface* s, SDL_Renderer* r, int tileSizeDest, std::pair<int,int> dm );
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void updateOffset() = 0;

	std::pair<int, int> drawOffset;// x offset first, y offset second
	int drawoffsetSpeed;

	std::pair<int, int> dimension;
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Surface* windowSurface;
	int tileSizeDest;
	virtual ~Scene();
};
