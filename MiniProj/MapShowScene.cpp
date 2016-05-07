#include "MapShowScene.h"

//Well this shit isn't written well sorry but i have submission tomorrow and it needs to work, I will refactor it someday hopefully Peace.......

string getString( int num )
{
	string ret;
	while (num > 0)
	{
		int dig = num % 10;
		num = num / 10;
		ret.push_back('0' + dig);
	}
	reverse( ret.begin(), ret.end() );
	return ret;
}

void MapShowScene::init(SDL_Window* w, SDL_Surface* s, SDL_Renderer* r, int tsd, pair<int,int> d, Map *m, TTF_Font* gF)
{
	Scene::init(w, s, r, tileSizeDest, d,gF);
	curMap = m;
	bomberman.tileSizeDest = tileSizeDest;
	enemies.tileSizeDest = tileSizeDest;
	bomb = nullptr;

	bomberman.setRenderer(renderer);
	bomberman.setImage("res//george.png");
	bomberman.mms = this;
	bomberman.screenDimension = dimension;
	enemies.setRenderer(renderer);
	enemies.setImage("res//spritesheetBalloon.png");

	curMap->drawOffsetPtr = &drawOffset;
	enemies.drawOffsetPtr = &drawOffset;
	bomberman.init(this);
	enemies.init(this);
	mapShowState = MapShowState::GAME_RUNNING;
	timeLeft = 60 * 1000;
	s_timeLeft = SDL_GetTicks();
	statusString.init(renderer, fontColor, "", gFont);
	{
		int w, h, offset = 200;
		SDL_GetWindowSize(window, &w, &h);
		statusString.pos = { offset, 10, w - 2 * offset, 50 };
	}
	
}


void MapShowScene::update()
{
	string temp;
	switch (mapShowState)
	{
	case MapShowState::GAME_RUNNING:
		bomberman.update();
		enemies.update();
		checkEnemies_Bomberman();
		updateOffset();
		if (bomb != nullptr)
		{
			bomb->update();
			if (bomb->bombState == BombState::DESTROYED)
			{
				delete bomb;
				bomb = nullptr;
			}
			checkBomb_Char();
		}
		else
		{
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			if (currentKeyStates[SDL_SCANCODE_SPACE])
			{
				putBomb();
			}
		}
		if ( SDL_GetTicks() - s_timeLeft > timeLeft )
		{
			mapShowState = MapShowState::GAME_OVER;
		}
		
		temp = "Time Remaning : " + getString( ( timeLeft - SDL_GetTicks() + s_timeLeft ) / 1000 );
		statusString.setText(temp.c_str());
		break;
	case MapShowState::GAME_SUCCESS:
		break;
	case MapShowState::GAME_OVER:
		break;
	}
	
}


void MapShowScene::render()
{
	curMap->draw();

	//SDL_RenderDrawRect(renderer, &bomberman.pos);
	bomberman.draw();

	enemies.draw();
	statusString.draw();
	if (bomb != nullptr)bomb->draw();
	switch (mapShowState)
	{
	case MapShowState::GAME_RUNNING:
		break;
	case MapShowState::GAME_SUCCESS:
	{
		TextSprite ts;
		fontColor.b = 250;
		ts.init(renderer, fontColor, "You Win", gFont);
		int w, h;
		SDL_GetWindowSize(window, &w, &h);
		int smaller = 100;
		ts.pos = { smaller, smaller, w - smaller * 2, h - smaller * 2 };
		ts.draw();
	}
		break;
	case MapShowState::GAME_OVER:
	{
		TextSprite ts;
		fontColor.b = 250;
		ts.init(renderer, fontColor, "You Lost", gFont);
		int w, h;
		SDL_GetWindowSize(window, &w, &h);
		int smaller = 100;
		ts.pos = { smaller, smaller, w - smaller * 2, h - smaller * 2 };
		ts.draw();
	}
		break;
	}
	
}

void MapShowScene::updateOffset()
{
	drawOffset = make_pair(dimension.first / 2 - bomberman.pos.x, dimension.second / 2 - bomberman.pos.y);
}

MapShowScene::MapShowScene()
{
}

void MapShowScene::putBomb()
{
	pair<int,int> cellPos = Physics::getCellPosition( bomberman.pos, tileSizeDest );
	if (bomb != nullptr)return;
	bomb = new Bomb();
	bomb->tileSizeDest = tileSizeDest;
	bomb->setRenderer(renderer);
	bomb->setImage("res//bombAnimi.png");
	bomb->drawOffsetPtr = &drawOffset;
	bomb->init(this);
	bomb->pos.x = tileSizeDest * cellPos.first;
	bomb->pos.y = tileSizeDest * cellPos.second;
}

void MapShowScene::checkEnemies_Bomberman()
{
	SDL_Rect &bombermanRect = bomberman.pos;
	vector< vector<SDL_Rect*> > enemiesRects(1);
	for (auto itr = enemies.enemyList.begin(); itr != enemies.enemyList.end(); itr++)
	{
		if (itr->isDead)continue;
		SDL_Rect &r = itr->pos;
		enemiesRects[0].push_back(&r);
	}
	if (Physics::checkCollision(enemiesRects, bombermanRect))
	{
		mapShowState = MapShowState::GAME_OVER;
	}
}

void MapShowScene::checkBomb_Char()
{
	bool isSomeOneAlive = false;
	for (auto itr = enemies.enemyList.begin(); itr != enemies.enemyList.end();itr++ )
	{
		if ( !itr->isDead )
		{
			isSomeOneAlive = isSomeOneAlive | true;
		}
		if ( bomb != nullptr && !itr->isDead &&bomb->getInteraction( *itr ) == BombCharStatus::DESTORY )
		{
			itr->isPlaying = true;
		}
	}
	if ( !isSomeOneAlive )
	{
		mapShowState = MapShowState::GAME_SUCCESS;
	}
	if ( bomb != nullptr && bomb->getInteraction( bomberman ) == BombCharStatus::DESTORY )
	{
		mapShowState = MapShowState::GAME_OVER;
	}
}

MapShowScene::~MapShowScene()
{
}

