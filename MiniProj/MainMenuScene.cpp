#include "MainMenuScene.h"
#include "MainGame.h"


MainMenuScene::MainMenuScene()
{	
	isSelectingMap = false;
}

void MainMenuScene::init(SDL_Window* w, SDL_Surface* s, SDL_Renderer* r, int ts, std::pair<int, int> dm, TTF_Font* gF)
{
	Scene::init( w, s, r, ts, dm, gF );
	initTexts();
	curSelectedMap = &mg->curMapIndex;
}

void MainMenuScene::initTexts()
{
	writeAndPutText(title, "Bomberman", 25, -30, 500, 200);	
	writeAndPutText(startButton, "Start", 30, 200, 150, 60);
	writeAndPutText(leftArrow, "<-", 200, 200, 150, 60 );
	writeAndPutText(curMapName, mg->mapNames[0].c_str(), 350, 200, 450, 60);
	writeAndPutText(rightArrow, "->", 800, 200, 150, 60);
	writeAndPutText(exitButton, "Exit", 30, 270, 150, 60 );
	writeAndPutText(playButton, "Play", 800, 270, 150, 60 );
	
}

void MainMenuScene::update()
{
	//Internal Update
	title.update();
	startButton.update();
	exitButton.update();
	if (isSelectingMap)
	{
		leftArrow.update();
		curMapName.update();
		curMapName.setText(mg->mapNames[*curSelectedMap].c_str());
		rightArrow.update();
		playButton.update();

		int n = mg->mapNames.size();
		//Event Update
		if ( rightArrow.isMouseHover() && mg->isClicked() )
		{
			(*curSelectedMap) = ((*curSelectedMap) + 1) % n;
		}
		if ( leftArrow.isMouseHover() && mg->isClicked() )
		{
			(*curSelectedMap)--;
			if ( *curSelectedMap == -1 )
			{
				*curSelectedMap = n - 1;
			}
		}
		if ( playButton.isMouseHover() && mg->isClicked() )
		{
			mg->transition_MainMenu_MapShow();
		}
	}

	//Event Update
	if ( startButton.isMouseHover() && mg->isClicked() )
	{
		isSelectingMap = !isSelectingMap;
	}
	if (exitButton.isMouseHover() && mg->isClicked() )
	{
		mg->gameState = GameState::QUIT;
	}
	
}

void MainMenuScene::render()
{
	title.draw();
	startButton.draw();
	startButton.hightLightIfMouseHover();

	exitButton.draw();
	exitButton.hightLightIfMouseHover();

	if ( isSelectingMap )
	{
		leftArrow.draw();
		leftArrow.hightLightIfMouseHover();

		curMapName.draw();
		
		rightArrow.draw();
		rightArrow.hightLightIfMouseHover();

		playButton.draw();
		playButton.hightLightIfMouseHover();
	}
}

void MainMenuScene::updateOffset()
{
}

MainMenuScene::~MainMenuScene()
{
}


