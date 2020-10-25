#include "testScene.hpp"

void TestScene::Start() 
{
    std::cout<<"TestScene Started";
    vertices = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f}; 
     glGenBuffers(1, &VBO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO); 
     glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
     glEnableVertexAttribArray(0); 
}

void TestScene::Update(float delta) 
{
    program.bind();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

ResourcePack TestScene::getResources() 
{
    return ResourcePack({&program});
}


TestScene::TestScene(GameProcess* proc)
    :Scene(proc),
    program("shader.vert","shader.frag","basic program")
{
    
}
