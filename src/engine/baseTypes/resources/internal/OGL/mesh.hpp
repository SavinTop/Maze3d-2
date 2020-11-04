#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "texture.hpp"
#include "shader.hpp"
#include "string"
#include <stddef.h>
#include "baseTypes/containers/mesh.hpp"
#include "render/drawable.hpp"

namespace res::ogl{

class Mesh : public OpenGLResource, public Drawable {
public:
    Mesh();
    Mesh(const Containers::Mesh& meshContainer);

    void load() override;
    void unload() override;

    void setParams(const Containers::Mesh& meshContainer);
    void __draw(res::ogl::ShaderProgram& program) override;
private:
Containers::Mesh mesh;
unsigned int VAO, VBO, EBO;
};

}