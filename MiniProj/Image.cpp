#include "Image.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
using namespace std;

Image::Image()
{

}

Image::Image(SDL_Renderer* r, const char* path)
{
	renderer = r;
	image = IMG_LoadTexture(renderer, path);
}

void Image::draw()
{
	SDL_RenderCopy(renderer, image, &src, &pos);
}

Image::~Image()
{
}

void Image::setImage( const char* path )
{
	image = IMG_LoadTexture(renderer, path);
	cout << IMG_GetError() << endl;
}

void Image::setRenderer(SDL_Renderer* r)
{
	renderer = r;
}
