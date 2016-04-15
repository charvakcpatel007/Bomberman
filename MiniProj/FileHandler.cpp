#include "FileHandler.h"
#include <ctime>


FileHandler::FileHandler()
{
}


FileHandler::~FileHandler()
{
}

void FileHandler::fillFileNames(const char* path, vector<string> &files)
{
	char search_path[200];
	sprintf_s(search_path, "%s/*.*", path);
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path, &fd);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				files.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
}

void FileHandler::fillVec2D( const char* path, vector< vector<int> > &A  )
{
	ifstream curFile( path );

	int r, c;
	curFile >> r;
	curFile >> c;

	for (int i = 0; i < r; i++)
	{
		A.emplace_back( vector<int>( c ) );
		for (int j = 0; j < c; j++)
		{
			curFile >> A[i][j];
		} 
	}
	curFile.close();
}

void FileHandler::vec2DToFile(vector<vector<int>>& A)
{
	int r = A.size();
	int c = A[0].size();
	string fileName = "Map";
	long long int t = time(0);
	for (int i = 0; i < 5; i++ )
	{
		fileName.push_back('0' + t % 10);
		t = t / 10;
	}
	fileName += ".txt";
	ofstream curFile( fileName.c_str() );
	curFile << r << " " << c << endl;
	for (int i = 0; i < A.size(); i++ )
	{
		for (int j = 0; j < A[i].size(); j++ )
		{
			curFile << A[i][j] << " ";
		}
		curFile << endl;
	}
	curFile.close();
}
