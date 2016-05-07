#pragma once
#include <SDL.h>
#include "Image.h"
#include "GenericCharacter.h"
#include <vector>
class MapShowScene;

//Kind of special class I had to make
//It didnt fit in Image, Animation or Map class I have made before because it feels like the combination of Animation and Map

enum BombState
{
	INIT,
	BLASTING,
	DESTROYED
};

enum BombCharStatus
{
	COLLISION,
	DESTORY,
	NOTHING
};

class Bomb : public Image
{
public:
	Bomb();
	void init( MapShowScene* mms );
	void setLRUB();
	void update();
	virtual void draw() override;
	BombState bombState;
	int heightSrc;
	int widthSrc;
	vector<SDL_Rect> srcs;
	MapShowScene* mms;
	
	pair<int, int> *drawOffsetPtr;
	long s_blowTimeLeft;
	long blowTimeLeft;//ms Time left before the bomb blows

	long s_totalBlastTime;
	long totalBlastTime;//ms afterblast effects
	int tileSizeDest;
	double curAlpha;
	double addAlpha;
	int l, r, t, b;
	int radius;//Length of the bomb blast is of radius * tileSizeDest;
	BombCharStatus getInteraction( GenericCharacter &character );
	vector<SDL_Rect> blastCollider;
	virtual ~Bomb();

private:
	void drawForGivenPos( const SDL_Rect &curpos );
	pair<int,int> getReach( vector< vector<int> > &mapData, int r, int c, int rdiff, int cdiff );
};

