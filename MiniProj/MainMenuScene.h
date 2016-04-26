#pragma once
#include "Scene.h"
#include <SDL_ttf.h>

class MainMenuScene :
	public Scene
{
public:
	MainMenuScene();

	void update() override;
	void render() override;
	void updateOffset() override;
	TTF_Font* gFont;
	~MainMenuScene();
};

