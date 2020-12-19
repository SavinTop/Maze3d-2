#include "floorModel.hpp"

FloorModel::FloorModel() 
{
    
}

FloorModel::FloorModel(glm::vec2 size, const std::vector<std::shared_ptr<res::ogl::Texture>>& textures) 
{
    setParams(size, textures);
}

void FloorModel::setParams(glm::vec2 size, const std::vector<std::shared_ptr<res::ogl::Texture>>& textures) 
{
    Containers::Mesh tempmesh;

    const float tcMul = size.x/2.0;

    Containers::Vertex vertex1;
    vertex1.pos = glm::vec3(-size.x/2,0,-size.y/2);
    vertex1.texCoords = glm::vec2(0,0)*tcMul;
    vertex1.normal = glm::vec3(0,1,0);
    vertex1.Tangent = glm::vec3(1);
    vertex1.Bitangent = glm::vec3(1);

    Containers::Vertex vertex2;
    vertex2.pos = glm::vec3( size.x/2,0,-size.y/2);
    vertex2.texCoords = glm::vec2(1,0)*tcMul;
    vertex2.normal = glm::vec3(0,1,0);
    vertex2.Tangent = glm::vec3(1);
    vertex2.Bitangent = glm::vec3(1);

    Containers::Vertex vertex3;
    vertex3.pos = glm::vec3( size.x/2,0, size.y/2);
    vertex3.texCoords = glm::vec2(1,1)*tcMul;
    vertex3.normal = glm::vec3(0,1,0);
    vertex3.Tangent = glm::vec3(1);
    vertex3.Bitangent = glm::vec3(1);

    Containers::Vertex vertex4;
    vertex4.pos = glm::vec3(-size.x/2,0, size.y/2);
    vertex4.texCoords = glm::vec2(0,1)*tcMul;
    vertex4.normal = glm::vec3(0,1,0);
    vertex4.Tangent = glm::vec3(1);
    vertex4.Bitangent = glm::vec3(1);
    
    tempmesh.vertices = {vertex1, vertex2, vertex3, vertex4};
    tempmesh.indices = {2,1,0,  3,2,0};
    tempmesh.textures = textures;

    mesh.setParams(tempmesh);
}

void FloorModel::load() 
{
    if(loaded) return;
    mesh.load();
    loaded = mesh.isLoaded();
}

void FloorModel::unload() 
{
    if(!loaded) return;
    mesh.unload();
    loaded = mesh.isLoaded();
}

void FloorModel::InitializeSubResources(std::string groupName) 
{
    
}

void FloorModel::__draw(oglw::Shader& shader) 
{
    mesh.draw(shader);
}
