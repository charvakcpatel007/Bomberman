#include "MainGame.h"
#include "Timer.h"
#include<SDL.h>
#include<iostream>
#include<SDL_image.h>
#include "Image.h"
#include "Animation.h"
#include "Bomberman.h"
using namespace std;

SDL_Rect r;

MainGame::MainGame()
{
	tileSizeDest = 70;
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("MP3", 20, 30, 1250, 680, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	vsync = true;
	evnt = new SDL_Event();
	fpsTimer.start();
	desiredfps = 60;
	desiredTime = 1000.0f / desiredfps;
	gameState = GameState::PLAY;
	bomberman.tileSizeDest = MainGame::tileSizeDest;
	e.tileSizeDest = MainGame::tileSizeDest;

	bomberman.setRenderer(renderer);
	bomberman.setImage("res//george.png");
	e.setRenderer(renderer);
	e.setImage("res//spritesheetBalloon.png");

	loadMaps();
	
	bomberman.init(maps[0]);
	e.init(maps[0]);
}

void MainGame::loadMaps()
{
	vector<string> fn;
	FileHandler::fillFileNames( "maps", fn );
	for (int i = 0; i < fn.size(); i++)
	{
		string finalPath = "maps//" + fn[i];
		maps.push_back( Map() );
		Map &curMap = maps[maps.size() - 1];
		curMap.tileSizeDest = MainGame::tileSizeDest;
		curMap.setRenderer( renderer );
		curMap.setImage( "res//sheet.png" );
		pair<int,int> p = FileHandler::fillVec2D( finalPath.c_str() ,curMap.mapData );
		curMap.startRow = p.first;
		curMap.startColoumn = p.second;
		curMap.setUpCollider();
	}

}

void MainGame::loadRes()
{

}

void MainGame::run()
{
	gameLoop();
}

void MainGame::update()
{
	bomberman.update();
	e.update();
}

void MainGame::render()
{
	/*for (int i = 0; i < maps.size(); i++)
	{
		maps[i].draw();
	}*/
	maps[ 0 ].draw();
	//SDL_RenderDrawRect(renderer, &bomberman.pos);
	bomberman.draw();
	e.draw();
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

void MainGame::gameLoop()
{
	fpsTimer.stop();
	while (gameState != GameState::QUIT)
	{
		fpsTimer.start();
		processInput();
		update();
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		render();
		SDL_RenderPresent(renderer);
		float x = desiredTime - fpsTimer.getTicks();
		
	}
}

MainGame::~MainGame()
{
	SDL_Quit();
}
