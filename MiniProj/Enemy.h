#pragma once
#include "Animation.h"
#include "Map.h"
#include <cstdlib>
#include <ctime>
#include "GenericCharacter.h"
#include "Timer.h"


class Enemy : public GenericCharacter
{
public:
	Enemy();
	virtual void init(MapShowScene *m)override;
	void turnRandom();
	void update() override;
	void setDefaultSrcRect();
	virtual ~Enemy();
	int startC;
	int startR;
	pair<int, int> direction;//first represents X Second represents Y 
	int turnChance;
	int startTime;
	int duration;
	bool isDead;
	pair<int,int> getLeft();
	pair<int,int> getRight();
private:
	
};

