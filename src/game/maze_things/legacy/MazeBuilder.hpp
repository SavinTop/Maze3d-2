#pragma once

#include <algorithm>
#include <stack>

#include <stdlib.h>
#include <time.h>
#include <cstring>

struct intVec2
{
	intVec2(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	intVec2 operator + (intVec2 const &right)
	{
		return intVec2(this->x+right.x, this->y+right.y);
	}

	int x, y;
};

class MazeBuilder
{
public:
	MazeBuilder(int w, int h);
	~MazeBuilder();

	//void RebuildMaze();
	void getWalls(bool** &vWalls, bool** &hWalls, int &width, int &height);

private:
	int m_width, m_height;
	int m_walls_w, m_walls_h;
	bool** m_vWallsArr;
	bool** m_hWallsArr;
	bool** m_RatMap;

	std::stack<intVec2> m_stack;
	intVec2 m_currentPosition;

	void buildMaze();
	bool canGo(intVec2);
};