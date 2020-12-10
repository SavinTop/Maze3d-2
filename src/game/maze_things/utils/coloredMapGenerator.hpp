#pragma once

#include "baseTypes/color.hpp"
#include "baseTypes/containers/Image.hpp"
#include "maze_things/legacy/MazeBuilder.hpp"

class ColoredMapGenerator{
public:
    void generateMap(MazeBuilder& mb);
    Containers::Image& getImg(){return img;};
private:
    Containers::Image img;
};