#pragma once

#include<vector>

#include <glm/glm.hpp>
#include "MazeBuilder.hpp"
#include "render/drawableHolder.hpp"
#include <memory>
//#include "Object3d.h"
//#include "LOG.h"

enum wallType
{
	Horizontal, Vertical, Corner, Root
};

struct mazeObject
{
	bool inescapable = false;
	DrawableHolder model;
	wallType wt;
	glm::ivec4 fw;
	glm::ivec4 sw;
	glm::ivec2 sector10;
	std::shared_ptr<DrawableHolder> child;
};

class ObjectMazeMap
{
public:
	ObjectMazeMap();
	ObjectMazeMap(MazeBuilder& maze, DrawableHolder rootWall, DrawableHolder lineWall, DrawableHolder cornerWall, DrawableHolder xmas_tree);

	mazeObject* get(int x, int y);

	unsigned int width();
	unsigned int height();
	void init(MazeBuilder& maze, DrawableHolder rootWall, DrawableHolder lineWall, DrawableHolder cornerWall, DrawableHolder xmas_tree);
	std::vector<std::vector<mazeObject>>& getMap();
private:

	std::vector<std::vector<mazeObject>> m_map;
};