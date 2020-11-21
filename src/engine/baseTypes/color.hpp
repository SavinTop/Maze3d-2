#pragma once

#include <cstdint>
#include <glm/glm.hpp>

namespace Color{

    struct ColorStruct;

    ColorStruct fromInt(int32_t color);

    int32_t rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

    int32_t rgba(const ColorStruct& clr);

    glm::vec4 getOglColor(int32_t color);
}