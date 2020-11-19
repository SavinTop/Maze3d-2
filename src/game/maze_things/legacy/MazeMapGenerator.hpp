#pragma once

#include "MazeBuilder.hpp"
#include <vector>

class MazeMapGenerator
{
public:
    MazeMapGenerator();
	MazeMapGenerator(MazeBuilder& maze);
    MazeMapGenerator(MazeMapGenerator&& move);
    MazeMapGenerator(MazeMapGenerator& copy);
	~MazeMapGenerator();

	unsigned char* getData();
	int getWidth();
	int getHeight();

private:
	unsigned char* m_data = nullptr;
	int m_width;
	int m_height;
};

