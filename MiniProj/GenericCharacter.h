#pragma once
#include "Map.h"
#include "Animation.h"
class MapShowScene;

class GenericCharacter : public Animation
{
public:
	GenericCharacter();
	virtual ~GenericCharacter() override;
	virtual void init(MapShowScene *m) = 0;
	virtual void update() = 0;

	int moveSpeed;
	const static int speed = 8;
	int collideroffset;
	MapShowScene *mms;
	int srcTileX;
	int srcTileY;
};

