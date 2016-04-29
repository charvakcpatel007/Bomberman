#pragma once
#include "Map.h"
#include "Physics.h"
class ClickableMap :
	public Map
{
public:
	ClickableMap();
	void draw() override;
	void update();
	pair<int, int> curTile;//First is row and Second is coloumn
	void processClick();
	void processDrag();
	virtual ~ClickableMap() ;
	int highLightThickness;
	bool isMousePressed;
	Image bomberman;
	Image enemy;
	void processHotkeyPress();
	void setImage(const char* path) override;
	bool isBombermanPresent;
	void expandRow();
	void expandColoumn();
	void contractRow();
	void contractColoumn();
protected:
	void setCurTile();
	void highLightCurTile();
	void addCharImages();
	
};

