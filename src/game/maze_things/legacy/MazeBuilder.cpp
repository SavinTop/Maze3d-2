#include "MazeBuilder.hpp"

MazeBuilder::MazeBuilder(int w, int h)
{
	setParams(w,h);
}

MazeBuilder::~MazeBuilder()
{
	for (int i = 0; i < m_walls_w; i++)
	{
		delete[] m_hWallsArr[i];
		delete[] m_vWallsArr[i];
	}

	delete[] m_hWallsArr;
	delete[] m_vWallsArr;

	for (int i = 0; i < m_width; i++)
		delete[] m_RatMap[i];

	delete[] m_RatMap;
}

void MazeBuilder::setParams(int w, int h) 
{
	m_width = w;
	m_height = h;
	m_walls_w = w+1;
	m_walls_h = h+1;
	m_currentPosition = intVec2(0,0);

	m_hWallsArr = new bool*[m_walls_w];
	m_vWallsArr = new bool*[m_walls_w];

	for (int i = 0; i < m_walls_w; i++)
	{
		m_hWallsArr[i] = new bool[m_walls_h];
		memset(m_hWallsArr[i], true, m_walls_h);
		m_vWallsArr[i] = new bool[m_walls_h];
		memset(m_vWallsArr[i], true, m_walls_h);
	}

	m_RatMap = new bool*[m_width];

	for (int i = 0; i < m_width; i++)
		m_RatMap[i] = new bool[m_height]();
}

void MazeBuilder::buildMaze()
{
	const intVec2 dirs[4] =
	{
		intVec2(0,-1),
		intVec2(1, 0),
		intVec2(0, 1),
		intVec2(-1, 0)
	};

	m_stack.push(m_currentPosition);
	int counterForRand = 0;

	while (m_stack.size())
	{
		short inds[] = {0,1,2,3};
		
		srand(time(NULL)+counterForRand++);

		for (int i = 0; i < 4; i++)
		{
			int swapInd = rand() % 4;
			std::swap(inds[i], inds[swapInd]);
		}

		bool dirWasFound = false;
		int dirIndex = 0;

		for (int i = 0; i < 4; i++)
		{
			int rInd = inds[i];
			if (canGo(m_currentPosition + dirs[rInd]))
			{
				dirIndex = rInd;
				dirWasFound = true;
				break;
			}
		}

		if (dirWasFound)
		{
			switch (dirIndex)
			{
			case 0: m_hWallsArr[m_currentPosition.x][m_currentPosition.y] = false; break;
			case 1: m_vWallsArr[m_currentPosition.x+1][m_currentPosition.y] = false; break;
			case 2: m_hWallsArr[m_currentPosition.x][m_currentPosition.y+1] = false; break;
			case 3: m_vWallsArr[m_currentPosition.x][m_currentPosition.y] = false; break;
			}

			m_currentPosition = m_currentPosition + dirs[dirIndex];
			m_RatMap[m_currentPosition.x][m_currentPosition.y] = true;
			m_stack.push(m_currentPosition);
		}
		else
		{
			m_currentPosition = m_stack.top();
			m_stack.pop();
		}
	}

	for (int h = 0; h < m_walls_h; h++)
		m_hWallsArr[m_walls_w-1][h] = false;
	for (int w = 0; w < m_walls_w; w++)
		m_vWallsArr[w][m_walls_h-1] = false;

	m_hWallsArr[0][0] = false;
	m_hWallsArr[m_walls_w-2][m_walls_h-1] = false;
}

bool MazeBuilder::canGo(intVec2 pos)
{
	if (pos.x<0 || pos.x>=m_width || pos.y<0 || pos.y>=m_height) return false;
	
	return !m_RatMap[pos.x][pos.y];
}

void MazeBuilder::getWalls(bool** &vWalls, bool** &hWalls, int &width, int &height)
{
	vWalls = m_vWallsArr;
	hWalls = m_hWallsArr;
	width = m_walls_w;
	height = m_walls_h;
}