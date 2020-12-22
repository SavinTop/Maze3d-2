#pragma once 

#include <glm/glm.hpp>
#include "render/drawableHolder.hpp"

struct laserObject{
    glm::vec3 start;
    glm::vec3 dir;
    bool destroyed = false;
    DrawableHolder holder;
};