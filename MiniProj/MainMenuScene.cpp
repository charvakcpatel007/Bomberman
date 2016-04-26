#include "MainMenuScene.h"
#include "TextSprite.h"


MainMenuScene::MainMenuScene()
{
}

void MainMenuScene::update()
{
}

void MainMenuScene::render()
{
	TextSprite ts;
	SDL_Color c = { 250, 0, 0, 1 };
	ts.init(renderer, c, "Hello", gFont);
	ts.pos = { 100, 100, 500, 100 };
	ts.draw();
	if( ts.isClicked() )
	{
		ts.hightLight();
	}
}

void MainMenuScene::updateOffset()
{
}

MainMenuScene::~MainMenuScene()
{
}
