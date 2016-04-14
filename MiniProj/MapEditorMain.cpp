#include "MapEditorMain.h"
#include "MouseHandler.h"

MapEditorMain::MapEditorMain()
{
	tileSizeDest = 70;
	drawOffset = make_pair( 0, 0 );
	curMap.tileSizeDest = tileSizeDest;
	curMap.setRenderer(renderer);
	curMap.setImage( "res//sheet.png" );
	vector< vector<int> > d = { { 2, 2, 2 }, { 2, 0, 2 }, { 2, 2, 2 } };
	curMap.mapData = d;
	curMap.drawOffsetPtr = &drawOffset;
	curMap.setUpCollider();
	curMap.isMousePressed = false;
}


MapEditorMain::~MapEditorMain()
{
}

void MapEditorMain::render()
{
	curMap.draw();
} 

void MapEditorMain::update()
{
	curMap.update();
}

void MapEditorMain::updateOffset()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP])
	{
		drawOffset.second += drawoffsetSpeed;
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN])
	{
		drawOffset.second -= drawoffsetSpeed;
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT])
	{
		drawOffset.first += drawoffsetSpeed;
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		drawOffset.first -= drawoffsetSpeed;
	}	
}

void MapEditorMain::processInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt) != 0)
	{
		switch (evnt.type)
		{
		case SDL_KEYDOWN:
			if( evnt.key.keysym.scancode == SDL_SCANCODE_R )
			{
				curMap.expandColoumn();
			}
			else if ( evnt.key.keysym.scancode == SDL_SCANCODE_D )
			{
				curMap.expandRow();
			}
			break;
		case SDL_QUIT:
			SDL_Quit();
			return;
			break;
		case SDL_MOUSEBUTTONDOWN:;
			curMap.isMousePressed = 1;
		}
	}
}
