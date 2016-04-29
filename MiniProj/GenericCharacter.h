#pragma once
#include "Map.h"
#include "Animation.h"

class GenericCharacter : public Animation
{
public:
	GenericCharacter();
	virtual ~GenericCharacter() override;
	virtual void init(Map *m) = 0;
	virtual void update() = 0;

	int moveSpeed;
	const static int speed = 8;
	int collideroffset;
	Map *map;
	int srcTileX;
	int srcTileY;
};

