#pragma once

#include "baseTypes/resources/internal/OGL/texture.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <memory>

namespace Containers{

struct Vertex{
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
    Vertex(){}
    Vertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec2& texCoords){
        this->pos = pos;
        this->normal = normal;
        this->texCoords = texCoords;
    }
};

class Mesh{
public:
    Mesh();
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<std::shared_ptr<res::ogl::Texture>>& textures);
    void setParams(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<std::shared_ptr<res::ogl::Texture>>& textures);

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<res::ogl::Texture>> textures;
};

}