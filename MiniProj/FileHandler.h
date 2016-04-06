#pragma once
#include <Windows.h>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;
class FileHandler
{
public:
	FileHandler();
	~FileHandler();
	static void fillFileNames(const char* path, vector<string> &files);
	static void fillVec2D( const char* path, vector< vector<int> > &A );
};

