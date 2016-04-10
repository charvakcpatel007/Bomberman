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
	virtual void init(Map &m) override;
	void turnRandom();
	void update() override;
	void draw() override;
	~Enemy();
	int startC;
	int startR;
	pair<int, int> direction;//first represents X Second represents Y 
	int turnChance;
	int startTime;
	int duration;
	pair<int, int> *drawOffsetPtr;
	pair<int,int> getLeft();
	pair<int,int> getRight();
private:
	
};

