#pragma once
#include<SDL.h>
#include<vector>
#include<SDL_image.h>
using namespace std;

enum DIR
{
	DOWN,
	LEFT,
	UP,
	RIGHT
};

class Animation
{
public:
	Animation();
	Animation( SDL_Renderer*  r, const char* path);
	virtual ~Animation();

	virtual void draw();
	void setImage(const char* path);
	void setRenderer( SDL_Renderer* r);
	virtual void update();		
	
	vector< vector< SDL_Rect > > srcFrameRects;//setting Rect for source image
	int getCurFrame();

	int noOfFrames;
	float curPosition;
	float strip;

	int rate;
	SDL_Rect src;
	SDL_Rect pos;
	
	bool isPlaying;
	int tileSizeDest;
	int magnificationOffset;
	pair<int, int> *drawOffsetPtr;
protected:
	SDL_Renderer* renderer;

	SDL_Texture* image;
};

