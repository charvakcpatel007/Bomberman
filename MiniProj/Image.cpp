#include "Image.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
using namespace std;

Image::Image()
{
	angle = 0;
}

Image::Image(SDL_Renderer* r, const char* path)
{
	renderer = r;
	image = IMG_LoadTexture(renderer, path);
}

void Image::draw()
{
	SDL_RenderCopyEx( renderer, image, &src, &pos, angle, NULL, SDL_FLIP_NONE );
}

void Image::draw(double angle)
{
	this->angle = angle;
	draw();
}

Image::~Image()
{
	SDL_DestroyTexture(image);
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
