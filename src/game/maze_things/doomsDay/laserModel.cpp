#include "laserModel.hpp"

LaserModel::LaserModel() 
{
    
}

LaserModel::LaserModel(glm::vec3 size) 
{
    setParams(size);
}

void LaserModel::setParams(glm::vec3 size) 
{
    Containers::Mesh temp;
    Containers::Vertex v1;
    v1.pos = glm::vec3(-size.x/2, -size.y/2, -size.z/2);
    Containers::Vertex v2;
    v2.pos = glm::vec3(+size.x/2, -size.y/2, -size.z/2);
    Containers::Vertex v3;
    v3.pos = glm::vec3(-size.x/2, +size.y/2, -size.z/2);
    Containers::Vertex v4;
    v4.pos = glm::vec3(+size.x/2, +size.y/2, -size.z/2);

    temp.vertices = {v1,v2,v3,v4};
    for(int i=0;i<4;i++)
    {
        auto t = temp.vertices[i];
        t.pos.z = +size.z/2;
        temp.vertices.push_back(t);
    }

    // temp.indices = {
    //     0,1,3,
    //     3,0,2,
    //     3,1,4,
    //     3,4,7};
    
    temp.indices = {
        3,1,0,
        3,0,2,

        5,1,3,
        7,5,3,

        4,5,7,
        6,4,7,

        1,5,4,
        1,4,0,
        
        0,4,6,
        0,6,2,

        3,2,6,
        3,6,7
        };

    mesh.setParams(temp);
}

void LaserModel::load() 
{
    if(loaded) return;
    mesh.load();
    loaded = mesh.isLoaded();
}

void LaserModel::unload() 
{
    if(!loaded) return;
    mesh.unload();
    loaded = mesh.isLoaded();
}

void LaserModel::__draw(oglw::Shader& shader) 
{
    mesh.draw(shader);
}
