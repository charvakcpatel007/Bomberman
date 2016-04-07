#pragma once
#include "Animation.h"
#include "Map.h"
#include "GenericCharacter.h"

class Enemy : public GenericCharacter
{
public:
	Enemy();
	virtual void init(Map &m) override;
	void update() override;
	~Enemy();
	int startC;
	int startR;
};

