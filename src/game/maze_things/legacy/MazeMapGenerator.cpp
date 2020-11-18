#include "MazeMapGenerator.hpp"

MazeMapGenerator::MazeMapGenerator(MazeBuilder& maze)
{
	int width;
	int height;
	bool **v_walls;
	bool **h_walls;
	maze.getWalls(v_walls, h_walls, width, height);
	
	m_width  =  width * 2 - 1;
	m_height = height * 2 - 1;

	m_data = new unsigned char[(m_width+1)*(m_height+1)*3]();

	for (int y = 0; y < height; y++)
	{
		int yPos = y * 2 * 3 * m_width+m_width*3-1;
		for (int x = 0; x < width; x++)
		{
			int pos = yPos - x*2*3-2;
			m_data[pos] = 100;

			if (h_walls[x][y]) 
				m_data[pos-3] = 100;
			if (v_walls[x][y]) 
				m_data[pos + m_width*3] = 100;
		}
	}

	int redByteStartPosition =  m_width*3*2-6;
	m_data[redByteStartPosition+1] = 255;

	int redByteEndPosition = m_width * 3 * (2 * (height-1)-1) + 3;
	m_data[redByteEndPosition] = 255;
	m_data[redByteEndPosition+1] = 255;
}

MazeMapGenerator::~MazeMapGenerator()
{
	if (m_data) delete[] m_data;
}

unsigned char* MazeMapGenerator::getData()
{
	return m_data;
}

int MazeMapGenerator::getWidth()
{
	return m_width;
}

int MazeMapGenerator::getHeight()
{
	return m_height;
}