#include<SDL.h>
#include "MainGame.h" 
#include <cstdio>
#include<string>
#include "FileHandler.h"
#include "Physics.h"
#include "MapEditorMain.h"
using namespace std;

int main(int argc, char* argv[])
{
	cout << "1. Play Game" << endl;
	cout << "2. Map Editor" << endl;
	cout << "Enter Choice : ";
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		{
			MainGame mg;
			mg.run();
		}
		break;
	case 2:
		{
			MapEditorMain mam;
			mam.run();
		}
		break;
	}
	
	return 0;
}