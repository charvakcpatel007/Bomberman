#include "PauseMenuScene.h"
#include "MainGame.h"


PauseMenuScene::PauseMenuScene()
{
}

void PauseMenuScene::init(SDL_Window* w, SDL_Surface* s, SDL_Renderer* r, int ts, std::pair<int, int> dm, TTF_Font* gF)
{
	Scene::init(w, s, r, ts, dm, gF);
	initTexts();
}

void PauseMenuScene::initTexts()
{
	writeAndPutText(pauseTitle, "Paused", 25, 0, 300, 150);
	writeAndPutText(resumeButton, "Resume", 30, 200, 150, 60);
	writeAndPutText(mainMenuButton, "Main Menu", 30, 270, 225, 60);
	writeAndPutText(exitButton, "Exit", 30, 340, 100, 60);
}

void PauseMenuScene::update()
{
	//Internal Updates
	pauseTitle.update();
	resumeButton.update();
	mainMenuButton.update();
	exitButton.update();

	//Event Handling
	if ( resumeButton.isMouseHover() && mg->isClicked() )
	{
		mg->gameState = GameState::PLAY;
	}
	if ( mainMenuButton.isClicked() && mg->isClicked() )
	{
		mg->gameState = GameState::PLAY;//Just for the sake of clarity no need to write
		mg->transition_MapShow_MainMenu();
	}
	if ( exitButton.isClicked() && mg->isClicked() )
	{
		mg->gameState = GameState::QUIT;
	}
} 

void PauseMenuScene::render()
{
	pauseTitle.draw();
	resumeButton.draw();
	resumeButton.hightLightIfMouseHover();
	mainMenuButton.draw();
	mainMenuButton.hightLightIfMouseHover();
	exitButton.draw();
	exitButton.hightLightIfMouseHover();
}

void PauseMenuScene::updateOffset()
{
}

PauseMenuScene::~PauseMenuScene()
{
}


