#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "texture.hpp"
#include "shader.hpp"
#include "string"
#include <stddef.h>
#include "baseTypes/containers/mesh.hpp"

namespace res::ogl{

class Mesh : public OpenGLResource{
public:
    Mesh();
    Mesh(const Containers::Mesh& meshContainer);

    void load() override;
    void unload() override;

    void setParams(const Containers::Mesh& meshContainer);
    void draw(ShaderProgram& shader);
private:
Containers::Mesh mesh;
unsigned int VAO, VBO, EBO;
};

}