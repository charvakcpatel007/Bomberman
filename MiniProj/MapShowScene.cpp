#include "MapShowScene.h"


void MapShowScene::init(SDL_Window* w, SDL_Surface* s, SDL_Renderer* r, int tsd, pair<int,int> d, Map *m, TTF_Font* gF)
{
	Scene::init(w, s, r, tileSizeDest, d,gF);
	curMap = m;
	bomberman.tileSizeDest = tileSizeDest;
	enemies.tileSizeDest = tileSizeDest;

	bomberman.setRenderer(renderer);
	bomberman.setImage("res//george.png");
	bomberman.map = m;
	bomberman.screenDimension = dimension;
	enemies.setRenderer(renderer);
	enemies.setImage("res//spritesheetBalloon.png");

	curMap->drawOffsetPtr = &drawOffset;
	enemies.drawOffsetPtr = &drawOffset;
	bomberman.init(m);
	enemies.init(m);
}


void MapShowScene::update()
{
	bomberman.update();
	
	enemies.update();
	
	checkEnemies_Bomberman();
	updateOffset();
	
}


void MapShowScene::render()
{
	curMap->draw();
	
	//SDL_RenderDrawRect(renderer, &bomberman.pos);
	bomberman.draw();
	
	enemies.draw();
}

void MapShowScene::updateOffset()
{
	drawOffset = make_pair(dimension.first / 2 - bomberman.pos.x, dimension.second / 2 - bomberman.pos.y);
}

MapShowScene::MapShowScene()
{
}

void MapShowScene::checkEnemies_Bomberman()
{
	SDL_Rect &bombermanRect = bomberman.pos;
	vector< vector<SDL_Rect*> > enemiesRects(1);
	for (int i = 0; i < enemies.enemyList.size(); i++)
	{
		SDL_Rect &r = enemies.enemyList[i].pos;
		enemiesRects[0].push_back(&r);
	}
	if (Physics::checkCollision(enemiesRects, bombermanRect))
	{
		//put game end code here
	}
}


MapShowScene::~MapShowScene()
{
}

