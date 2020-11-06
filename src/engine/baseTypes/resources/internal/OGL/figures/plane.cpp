#include "plane.hpp"


namespace res::ogl
{
    Plane::Plane(glm::vec3 position, glm::vec2 size, std::vector<Texture*> textures) 
    {
        setParams(position, size, textures);
    }
    
    Plane::Plane(Containers::Mesh& mesh) 
    {
        setParams(mesh);
    }
    
    void Plane::load() 
    {
        mesh_.load();
        loaded = mesh_.isLoaded();
    }
    
    void Plane::unload() 
    {
        mesh_.unload();
        loaded = mesh_.isLoaded();
    }
    
    void Plane::setParams(glm::vec3 position, glm::vec2 size, std::vector<Texture*>& textures) 
    {
        this->position = position;
        Containers::Mesh temp;
        std::vector<Containers::Vertex> tempVertices = {
            Containers::Vertex(glm::vec3(-size.x/2, -size.y/2, 0),glm::vec3(0,0,1), glm::vec2(0,0)),
            Containers::Vertex(glm::vec3(+size.x/2, -size.y/2, 0),glm::vec3(0,0,1), glm::vec2(1,0)),
            Containers::Vertex(glm::vec3(+size.x/2, +size.y/2, 0),glm::vec3(0,0,1), glm::vec2(1,1)),
            Containers::Vertex(glm::vec3(-size.x/2, +size.y/2, 0),glm::vec3(0,0,1), glm::vec2(0,1))
        };
        std::vector<unsigned> tempIndices = {
            0,1,2,
            2,0,3
        };
        temp.setParams(tempVertices, tempIndices, textures);
        mesh_.setParams(temp);
    }
    
    void Plane::setParams(Containers::Mesh& mesh) 
    {
        mesh_.setParams(mesh);
    }
    
    void Plane::__draw(ShaderProgram& program) 
    {
        mesh_.draw(program);
    }
}