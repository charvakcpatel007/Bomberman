#pragma once
#include "Scene.h"
#include <SDL_ttf.h>
#include "TextSprite.h"
#include <vector>
using namespace std;
//didnt go for general structure
//made direct layout and implemented everything here because its small.
class MainGame;

class MainMenuScene :
	public Scene
{
public:
	MainMenuScene();
	MainGame *mg;
	virtual void init(SDL_Window* w, SDL_Surface* s, SDL_Renderer* r, int tileSizeDest, std::pair<int, int> dm, TTF_Font* gF) override;
	void update() override;
	void render() override;
	void updateOffset() override;
	
	~MainMenuScene();
		

	TextSprite title;
	TextSprite startButton;
	TextSprite exitButton;

	//Map Selection Area
	TextSprite curMapName;
	TextSprite leftArrow;
	TextSprite rightArrow;
	TextSprite playButton;
	int *curSelectedMap;
	bool isSelectingMap;

private:
	void initTexts();
	
};

