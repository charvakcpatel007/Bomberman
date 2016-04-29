#include "TextSprite.h"
#include "MouseHandler.h"
#include "Physics.h"


TextSprite::TextSprite()
{
	pos = { 100, 100, 100, 100 };
	highLightThickness = 2;
	isClickedVar = false;
	mouseClickData = make_pair( 1, 1 );
}

void TextSprite::setText(const char* text)
{
	TextSprite::text = text;
	updateImage();
}

void TextSprite::init(SDL_Renderer* renderer, SDL_Color color, const char* text,TTF_Font* font)
{
	this->renderer = renderer;
	this->textColor = color;
	this->gFont = font;
	this->text = text;
	updateImage();
}

void TextSprite::updateImage()
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text, textColor);
	image = SDL_CreateTextureFromSurface(renderer, textSurface);
}

void TextSprite::draw( SDL_Color c)
{
	textColor = c;
	updateImage();
	draw();
}

void TextSprite::draw( )
{
	SDL_RenderCopy(renderer, image, nullptr, &pos);
}

void TextSprite::updateMouseData()
{
	mouseClickData.first = mouseClickData.second;
	mouseClickData.second = isCurrentlyClicked();
}

void TextSprite::update()
{
	updateMouseData();
}

void TextSprite::hightLight()
{
	SDL_Rect drawRect = pos;
	SDL_SetRenderDrawColor(renderer, 0, 0, 250, 1);
	for (int i = 0; i < highLightThickness; i++)
	{
		drawRect.x--;
		drawRect.y--;
		drawRect.w += 2;
		drawRect.h += 2;
		SDL_RenderDrawRect(renderer, &drawRect);
	}
}

void TextSprite::hightLightIfMouseHover()
{
	SDL_Rect mouseRect = MouseHandler::getPositionRectangle();
	if (Physics::checkCollision(mouseRect, pos))
	{
		hightLight();
	}
}

bool TextSprite::isMouseHover()
{
	SDL_Rect mouseRect = MouseHandler::getPositionRectangle();
	if (Physics::checkCollision(mouseRect, pos) )
	{
		return true;
	}
	return false;
}

bool TextSprite::isCurrentlyClicked()
{
	SDL_Rect mouseRect = MouseHandler::getPositionRectangle();
	if ( Physics::checkCollision( mouseRect, pos ) && MouseHandler::isLeftDown() )
	{
		return true;
	}
	return false;
	
}

bool TextSprite::isClicked()
{
	SDL_Rect mouseRect = MouseHandler::getPositionRectangle();
	if (Physics::checkCollision(mouseRect, pos) && mouseClickData.first == 0 && mouseClickData.second == 1)
	{
		return true;
	}
	return false;
}

TextSprite::~TextSprite()
{
	SDL_DestroyTexture(image);
}


