#pragma once

#include "collisionChecker.hpp"
#include "maze_things/legacy/ObjectMazeBuilder.hpp"
#include <set>

struct ray_params{
    glm::vec2 start;
    glm::vec2 end;
    glm::vec2 currPos;
    glm::vec2 step;
    bool collapsed;
};

class RaycastingHandler{
public:
    RaycastingHandler(int ray_count, ObjectMazeMap* mmp);
    RaycastingHandler(){};
    void recalculate(float fov, glm::vec2 camPos, float camDir);
    std::set<std::pair<int, int>>& getCollidedSectors(){return collidedSectors;};
private:
    int ray_count;
    ObjectMazeMap* mmp;
    std::vector<ray_params> rays;
    std::set<std::pair<int, int>> collidedSectors;
};