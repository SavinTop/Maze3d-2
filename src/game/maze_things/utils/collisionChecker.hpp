#pragma once

#include <glm/glm.hpp>
#include "maze_things/legacy/ObjectMazeBuilder.hpp"

static bool coll(glm::vec4 left, glm::vec4 right)
{
	if (left[2] < right[0] || right[2] < left[0]) return false;
	if (left[3] < right[1] || right[3] < left[1]) return false;

	return true;
};

static mazeObject *checkCollision(ObjectMazeMap &omm, glm::ivec2 sector, glm::vec4 playerRect)
{
    for (int y = sector.y - 1; y <= sector.y + 1; y++)
        for (int x = sector.x - 1; x <= sector.x + 1; x++)
        {
            mazeObject *temp = omm.get(x, y);
            if (temp)
            {
                auto t = *temp;
                auto firstColl = coll(playerRect, t.fw);
                if (firstColl)
                    return temp;
                if (t.wt == Corner)
                {
                    auto secondColl = coll(playerRect, t.sw);
                    if (secondColl)
                        return temp;
                }
            }
        }
    return nullptr;
}

static bool lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {

  float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
  float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

  if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
    return true;
  }
  return false;
}

static bool lineRect(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh) {

  bool left =   lineLine(x1,y1,x2,y2, rx,ry,rx, ry+rh);
  bool right =  lineLine(x1,y1,x2,y2, rx+rw,ry, rx+rw,ry+rh);
  bool top =    lineLine(x1,y1,x2,y2, rx,ry, rx+rw,ry);
  bool bottom = lineLine(x1,y1,x2,y2, rx,ry+rh, rx+rw,ry+rh);

  if (left || right || top || bottom) {
    return true;
  }
  return false;
}