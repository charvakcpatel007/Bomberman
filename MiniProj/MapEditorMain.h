#pragma once
#include "BasicGame.h"
#include "TextSprite.h"
#include "ClickableMap.h"
class MapEditorMain :
	public BasicGame
{
public:
	MapEditorMain();
	virtual ~MapEditorMain();

	void render() override;
	void update() override;
	void updateOffset() override;
	void processInput() override;
	ClickableMap curMap;
	int margin;
};

