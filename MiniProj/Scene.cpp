#include "Scene.h"


Scene::Scene()
{
	drawoffsetSpeed = 15;
	fontColor = { 250, 0, 0, 1 };
}

void Scene::init( SDL_Window* w, SDL_Surface* s, SDL_Renderer* r, int tsd, std::pair<int,int> d, TTF_Font* gF )
{
	window = w;
	windowSurface = s;
	renderer = r;
	tileSizeDest = tsd;
	dimension = d;
	gFont = gF;
}

void Scene::writeAndPutText(TextSprite& curText, const char* text, int x, int y, int w, int h)
{

	curText.init(renderer, fontColor, text, gFont);
	curText.pos = { x, y, w, h };
}

Scene::~Scene()
{
}
