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