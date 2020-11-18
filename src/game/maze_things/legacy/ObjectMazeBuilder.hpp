#pragma once

#include<vector>

#include <glm/glm.hpp>
#include "MazeBuilder.hpp"
//#include "Object3d.h"
//#include "LOG.h"

enum wallType
{
	Horizontal, Vertical, Corner, Root
};

struct mazeObject
{
	bool inescapable = false;
	//Object3d model;
	wallType wt;
	glm::ivec4 fw;
	glm::ivec4 sw;
};

class ObjectMazeMap
{
public:

	ObjectMazeMap(MazeBuilder& maze);

	mazeObject* get(int x, int y);

	unsigned int width();
	unsigned int height();

private:

	std::vector<std::vector<mazeObject>> m_map;
};