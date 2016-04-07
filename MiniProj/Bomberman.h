#pragma once
#include "Animation.h"
#include <SDL.h>
#include "Physics.h"
#include "GenericCharacter.h"
#include "Map.h"
class Bomberman : public GenericCharacter
{
public:
	Bomberman();
	virtual void init(Map &m) override;
	virtual void update() override;
	~Bomberman();
private:
	pair<int,int> getPositionFromMap();
};

