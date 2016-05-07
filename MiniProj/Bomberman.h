#pragma once
#include "Animation.h"
#include <SDL.h>
#include "Physics.h"
#include "GenericCharacter.h"
#include "Map.h"
class MapShowScene;
class Bomberman : public GenericCharacter
{
public:
	Bomberman();
	virtual void init(MapShowScene *m) override;
	virtual void update() override;
	virtual void draw() override;
	pair<int, int> screenDimension;
	virtual void setDefaultSrcRect();
	virtual ~Bomberman() override;
private:
	pair<int,int> getPositionFromMap();
};

