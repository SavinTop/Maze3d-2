#pragma once

#include "render/drawable.hpp"
#include "baseTypes/resources/internal/OGL/mesh.hpp"

class LaserModel : public OpenGLResource, public Drawable{
public:
    LaserModel();
    LaserModel(glm::vec3 size);

	void setParams(glm::vec3 size);

    void load() override;
    void unload() override;
    void __draw(oglw::Shader& shader) override;
private:
    res::ogl::Mesh mesh;
};