#include "MainGame.h"
#include "Timer.h"
#include<SDL.h>
#include<iostream>
#include<SDL_image.h>
#include "Image.h"
#include "Animation.h"
#include "Bomberman.h"
#include <ctime>
#include <cstdlib>
using namespace std;

MainGame::MainGame()
{
	tileSizeDest = 70;
	curMap = nullptr;
	gameState = GameState::MAINMENU;
	loadMaps();

	mainMenu.mg = this;
	mainMenu.init(window, windowSurface, renderer, tileSizeDest, dimension, gFont);

	pauseMenu.mg = this;
	pauseMenu.init(window, windowSurface, renderer, tileSizeDest, dimension, gFont);
	
	loadMaps();
	curMapIndex = 0;

	mss = nullptr;
}

void MainGame::loadMaps()
{
	FileHandler::fillFileNames( "maps", mapNames );
}

void MainGame::updateOffset()
{
	
}

void MainGame::loadMap( string &mapName )
{
	if ( curMap != nullptr )
	{
		delete curMap;
	}
	string finalPath = "maps//" + mapName;
	
	curMap = new Map();
	curMap->tileSizeDest = MainGame::tileSizeDest;
	curMap->setRenderer(renderer);
	curMap->setImage("res//sheet.png");
	FileHandler::fillVec2D(finalPath.c_str(), curMap->mapData);
	curMap->setUpCollider();
}

void MainGame::transition_MainMenu_MapShow()
{
	gameState = GameState::PLAY;
	loadMap( mapNames[ curMapIndex ] );
	if ( mss != nullptr )
	{
		delete mss;
	}
	mss = new MapShowScene();
	mss->tileSizeDest = MainGame::tileSizeDest;
	mss->init(window, windowSurface, renderer, tileSizeDest, dimension, curMap, gFont);
}

void MainGame::transition_MapShow_MainMenu()
{
	delete mss;
	mss = nullptr;
	gameState = GameState::MAINMENU;
	mainMenu.isSelectingMap = false;
}


void MainGame::loadRes()
{

}

void MainGame::update()
{
	switch ( gameState )
	{
	case GameState::MAINMENU:
		mainMenu.update();
		break;
	case GameState::PLAY:
		mss->update();
		break;
	case GameState::PAUSE:
		pauseMenu.update();
		break;
	}
}

void MainGame::render()
{
	switch (gameState)
	{
	case GameState::MAINMENU:
		mainMenu.render();
		break;
	case GameState::PLAY:
		mss->render();
		break;
	case GameState::PAUSE:
		pauseMenu.render();
		break;
	}
	
}



void MainGame::processInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt) != 0 )
	{
		switch (evnt.type)
		{
		case SDL_KEYDOWN:
			if ( evnt.key.keysym.scancode == SDL_SCANCODE_ESCAPE  )
			{
				switch ( gameState )
				{
				case GameState::PLAY :
					gameState = GameState::PAUSE;
					break;
				case GameState::PAUSE:
					gameState = GameState::PLAY;
					break;
				}
			}
			break;
		case SDL_QUIT:
			SDL_Quit();
			return;
			break;
		case SDL_MOUSEBUTTONDOWN:;
		}
	}
}

MainGame::~MainGame()
{
	SDL_Quit();
}
