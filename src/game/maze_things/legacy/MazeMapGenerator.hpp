#pragma once

#include "MazeBuilder.hpp"
#include <vector>

class MazeMapGenerator
{
public:
	MazeMapGenerator(MazeBuilder& maze);
	~MazeMapGenerator();

	unsigned char* getData();
	int getWidth();
	int getHeight();

private:
	unsigned char* m_data;
	int m_width;
	int m_height;
};

