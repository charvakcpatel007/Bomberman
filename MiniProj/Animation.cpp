#include "Animation.h"
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "MainGame.h"
#include <iostream>
using namespace std;

Animation::Animation()
{
	strip = 0;
	rate = 1.0f;
	curPosition = 0.0f;
	strip = 0;
	isPlaying = false;
	magnificationOffset = 20;
}

Animation::Animation( SDL_Renderer* r, const char* path)
{
	renderer = r;
	image = IMG_LoadTexture(renderer, path);
}

Animation::~Animation()
{

}

int Animation::getCurFrame()
{
	float block = 100 / (float)noOfFrames;
	return (int)( curPosition / block );
}

void Animation::update()
{
	curPosition += rate;
	if (curPosition >= 100)curPosition -= 100;
}

void Animation::draw()
{
	SDL_Rect intermediatepos = pos;
	intermediatepos.x -= magnificationOffset;
	intermediatepos.y -= magnificationOffset;
	intermediatepos.x += drawOffsetPtr->first;
	intermediatepos.y += drawOffsetPtr->second;
	intermediatepos.h += magnificationOffset * 2;
	intermediatepos.w += magnificationOffset * 2;
	SDL_RenderCopy(renderer, image, isPlaying ? &srcFrameRects[strip][getCurFrame()] : &srcFrameRects[strip][0], &intermediatepos);
}

void Animation::setImage(const char* path)
{
	image = IMG_LoadTexture(renderer, path);
}

void Animation::setRenderer(SDL_Renderer* r)
{
	renderer = r;
}
