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
	bomberman.tileSizeDest = MainGame::tileSizeDest;
	enemies.tileSizeDest = MainGame::tileSizeDest;

	bomberman.setRenderer(renderer);
	bomberman.setImage("res//george.png");
	bomberman.screenDimension = dimension;
	enemies.setRenderer(renderer);
	enemies.setImage("res//spritesheetBalloon.png");
	loadMaps();
	maps[0].drawOffsetPtr = &drawOffset;
	enemies.drawOffsetPtr = &drawOffset;
	
	bomberman.init(maps[0]);
	enemies.init(maps[0]);
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
	drawOffset = make_pair( dimension.first / 2 - bomberman.pos.x, dimension.second / 2 - bomberman.pos.y );
}

void MainGame::loadRes()
{

}

void MainGame::update()
{
	
	bomberman.update();
	enemies.update();
	updateOffset();
	//e.update();
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
	enemies.draw();
	//e.draw();
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
