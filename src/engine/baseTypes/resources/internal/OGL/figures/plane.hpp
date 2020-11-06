#pragma once 

#include "baseTypes/resource/resource.hpp"
#include <baseTypes/resources/internal/OGL/mesh.hpp>
#include <glm/glm.hpp>

namespace res::ogl{

class Plane : public Resource, public Drawable{
public:
    Plane(glm::vec3 position = glm::vec3(0), glm::vec2 size = glm::vec2(1.0), std::vector<Texture*> textures = {});
    Plane(Containers::Mesh& mesh);

    void load() override;
    void unload() override;

    void setParams(glm::vec3 position, glm::vec2 size, std::vector<Texture*>& textures);
    void setParams(Containers::Mesh& mesh);

    void __draw(ShaderProgram& program) override;
private:
    Mesh mesh_;
    glm::vec2 size;
};

}