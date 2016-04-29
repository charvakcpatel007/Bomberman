#pragma once
#include <SDL_ttf.h>
#include "Image.h"
class TextSprite
{
public:
	TextSprite();
	void setText(const char* text);
	void init(SDL_Renderer* renderer, SDL_Color color, const char* text,TTF_Font* font );
	void updateImage();
	void draw(  SDL_Color c);
	void draw();
	void update();
	void hightLight();
	void hightLightIfMouseHover();
	bool isMouseHover();
	bool isCurrentlyClicked();
	bool isClicked();
	bool isClickedVar;
	~TextSprite();
	const char* text;
	SDL_Color textColor;
	SDL_Rect pos;
	SDL_Renderer* renderer;
	SDL_Texture* image;
	TTF_Font* gFont;
	int highLightThickness;
private:
	pair<bool, bool> mouseClickData;
	void updateMouseData();
};

