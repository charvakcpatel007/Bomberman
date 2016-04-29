#pragma once
#include "Scene.h"
#include <SDL_ttf.h>
#include "TextSprite.h"
#include <vector>
class MainGame;
using namespace std;


class PauseMenuScene :
	public Scene
{
public:
	PauseMenuScene();
	MainGame *mg;
	virtual void init(SDL_Window* w, SDL_Surface* s, SDL_Renderer* r, int tileSizeDest, std::pair<int, int> dm, TTF_Font* gF) override;
	void update() override;
	void render() override;
	void updateOffset() override;
	~PauseMenuScene();

	TextSprite pauseTitle;
	TextSprite resumeButton;
	TextSprite mainMenuButton;
	TextSprite exitButton;
private:
	void initTexts();
};

