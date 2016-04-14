#include "TextSprite.h"


TextSprite::TextSprite()
{
	pos = { 0, 0, 100, 100 };
}

void TextSprite::setImage(const char* text)
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

TextSprite::~TextSprite()
{
}
