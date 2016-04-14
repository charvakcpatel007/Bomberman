#pragma once
#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
using namespace std;
class Image
{
public:
	Image();
	Image(SDL_Renderer* r, const char* filePath);
	virtual void draw();
	virtual void setImage( const char* path );
	virtual	void setRenderer( SDL_Renderer* r );
	~Image();
	SDL_Rect src;
	SDL_Rect pos;
	SDL_Renderer* renderer;
	SDL_Texture* image;
private:
protected:
};

