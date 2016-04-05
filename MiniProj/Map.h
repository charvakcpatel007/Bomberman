#pragma once
#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include "Image.h"
#include <Windows.h>
#include<vector>

using namespace std;

class Map : public Image
{
public:
	static const int OPEN = 0;
	static const int BRICK = 1;
	static const int BLOCK = 2;
	
	vector<SDL_Rect> tileSrc;
	int rows;
	int coloumns;
	int tileSize;

	int startRow;
	int startColoumn;
	vector< vector<int> > mapData;
	vector< vector<SDL_Rect> > mapCollider;
	void draw();
	Map();
	void setUpCollider();
	~Map();
	int tileSizeDest;
private:

};

