#include "mesh.hpp"

namespace Containers
{
    Mesh::Mesh() 
    {
        
    }
    
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<std::shared_ptr<res::ogl::Texture>>& textures) 
    {
        setParams(vertices, indices, textures);
    }
    
    void Mesh::setParams(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<std::shared_ptr<res::ogl::Texture>>& textures) 
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
    }
}