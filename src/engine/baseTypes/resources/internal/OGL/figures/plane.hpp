#pragma once 

#include <baseTypes/resources/internal/OGL/mesh.hpp>
#include <glm/glm.hpp>

namespace res::ogl{

class Plane{
public:
    Plane();
    Plane(glm::vec3 position, glm::vec2 size, std::vector<Texture*> textures);

    void draw(ShaderProgram& program);
private:
    Mesh mesh_;
    glm::vec3 position;
    glm::vec2 size;
};

}