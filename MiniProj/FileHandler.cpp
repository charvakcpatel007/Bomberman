#include "FileHandler.h"


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

pair<int,int> FileHandler::fillVec2D( const char* path, vector< vector<int> > &A  )
{
	ifstream curFile( path );

	int r, c;
	curFile >> r;
	curFile >> c;
	int startrow;
	int startcoloumn;
	curFile >> startrow;
	curFile >> startcoloumn;

	for (int i = 0; i < r; i++)
	{
		A.emplace_back( vector<int>( c ) );
		for (int j = 0; j < c; j++)
		{
			curFile >> A[i][j];
		} 
	}
	curFile.close();
	return make_pair( startrow, startcoloumn );
}
