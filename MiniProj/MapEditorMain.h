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
	void updateOffset();
	void processInput() override;
	ClickableMap curMap;
	int margin;
	pair<int, int> drawOffset;// x offset first, y offset second
	int drawoffsetSpeed;

};

