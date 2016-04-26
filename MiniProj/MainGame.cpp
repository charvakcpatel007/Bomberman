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
	loadMaps();
	mainMenu.init(window, windowSurface, renderer, tileSizeDest, dimension);
	mainMenu.gFont = gFont;
	mss.tileSizeDest = MainGame::tileSizeDest;
	mss.init(window, windowSurface, renderer, tileSizeDest, dimension, maps[1]);
}

void MainGame::loadMaps()
{
	vector<string> fn;
	FileHandler::fillFileNames( "maps", fn );
	for (int i = 0; i < fn.size(); i++)
	{
		string finalPath = "maps//" + fn[i];
		maps.emplace_back( );
		Map &curMap = maps[maps.size() - 1];
		curMap.tileSizeDest = MainGame::tileSizeDest;
		curMap.setRenderer( renderer );
		curMap.setImage( "res//sheet.png" );
		FileHandler::fillVec2D( finalPath.c_str() ,curMap.mapData );
		curMap.setUpCollider();
	}

}

void MainGame::updateOffset()
{
	
	
}



void MainGame::loadRes()
{

}

void MainGame::update()
{
	mainMenu.update();
	//mss.update();
}

void MainGame::render()
{
	mainMenu.render();
	//mss.render();
}



void MainGame::processInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt) != 0 )
	{
		switch (evnt.type)
		{
		case SDL_KEYDOWN:
			
			break;
		case SDL_QUIT:
			SDL_Quit();
			return;
			break;
		case SDL_MOUSEMOTION:;
		}
	}
}

MainGame::~MainGame()
{
	SDL_Quit();
}
