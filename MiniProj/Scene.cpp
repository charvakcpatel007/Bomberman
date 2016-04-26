#include "Scene.h"


Scene::Scene()
{
	drawoffsetSpeed = 15;
}

void Scene::init( SDL_Window* w, SDL_Surface* s, SDL_Renderer* r, int tsd, std::pair<int,int> d )
{
	window = w;
	windowSurface = s;
	renderer = r;
	tileSizeDest = tsd;
	dimension = d;
}

Scene::~Scene()
{
}
