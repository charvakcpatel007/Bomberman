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
	margin = 10;
	drawoffsetSpeed = 15;
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
	/*const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_W])
	{
		drawOffset.second += drawoffsetSpeed;
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_S])
	{
		drawOffset.second -= drawoffsetSpeed;
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A])
	{
		drawOffset.first += drawoffsetSpeed;
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D])
	{
		drawOffset.first -= drawoffsetSpeed;
	}	*/
	pair<int, int> curMousePos = MouseHandler::getMousePosition();
	pair<int, int> preCamState = drawOffset;
	if ( curMousePos.first <= 0 + margin )
	{
		drawOffset.first += drawoffsetSpeed;

	}
	else if ( curMousePos.first >= dimension.first - margin )
	{
		drawOffset.first -= drawoffsetSpeed;
	}

	if (curMousePos.second <= 0 + margin)
	{
		drawOffset.second += drawoffsetSpeed;
	}
	else if (curMousePos.second >= dimension.second - margin)
	{
		drawOffset.second -= drawoffsetSpeed;
	}

	if( !isCamInLimit( drawOffset, curMap ) )
	{
		drawOffset = preCamState;
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
			if ( evnt.key.keysym.scancode == SDL_SCANCODE_F )
			{
				if ( isFullScreen )
				{
					isFullScreen = false;
					SDL_SetWindowFullscreen(window, 0);
					SDL_GetWindowSize(window, &dimension.first, &dimension.second);
				}
				else
				{
					isFullScreen = true;
					dimension = make_pair( 1366, 768 );
					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
				}
			}
			if ( evnt.key.keysym.scancode == SDL_SCANCODE_G )
			{
				FileHandler::vec2DToFile(curMap.mapData);
			}
			if( evnt.key.keysym.scancode == SDL_SCANCODE_D )
			{
				curMap.expandColoumn();
			}
			else if ( evnt.key.keysym.scancode == SDL_SCANCODE_S )
			{
				curMap.expandRow();
			}
			else if (evnt.key.keysym.scancode == SDL_SCANCODE_W && curMap.mapData.size() > 3 )
			{
				curMap.contractRow();
			}
			else if (evnt.key.keysym.scancode == SDL_SCANCODE_A && curMap.mapData[ 0 ].size() > 3 )
			{
				curMap.contractColoumn();
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
