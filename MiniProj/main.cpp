#include<SDL.h>
#include "MainGame.h" 
#include <cstdio>
#include<string>
#include "FileHandler.h"
#include "Physics.h"
using namespace std;

int main(int argc, char* argv[])
{
	MainGame mg;
	mg.run();
	return 0;
}