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
	static const int BOMBERMAN = 3;
	static const int ENEMY = 4;
	
	vector<SDL_Rect> tileSrc;
	int rows;
	int coloumns;
	int tileSize;

	int noOfEnemies;
	
	vector< vector<int> > mapData;
	vector< vector<SDL_Rect> > mapCollider;
	virtual void draw();
	Map();
	void setUpCollider();
	virtual ~Map();
	int tileSizeDest;
private:

};

