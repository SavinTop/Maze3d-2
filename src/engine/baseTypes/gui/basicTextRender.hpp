#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H 

#include <glad/glad.h>
#include <string>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <baseTypes/oglWrappers/shader.hpp>
#include <utilities/fileLoader.hpp>

struct Character {
    unsigned int textureID;  
    glm::ivec2   Size;       
    glm::ivec2   Bearing;    
    unsigned int Advance;    
};

int guiText_init(int w, int h, std::string path);
void guiText_loadRangeOfCharacters(int from, int to);
void guiText_renderText(oglw::Shader &s, std::string text, float x, float y, float scale, glm::vec3 color);
oglw::Shader& guiText_getTextShader();