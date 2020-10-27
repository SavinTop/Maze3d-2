#include "testScene.hpp"

void _CheckGLError(const char* file, int line);

#define CheckGLError() _CheckGLError(__FILE__, __LINE__)

void _CheckGLError(const char* file, int line)
{
    GLenum err ( glGetError() );

    while ( err != GL_NO_ERROR )
    {
        std::string error;
        switch ( err )
        {
            case GL_INVALID_OPERATION:  error="INVALID_OPERATION";      break;
            case GL_INVALID_ENUM:       error="INVALID_ENUM";           break;
            case GL_INVALID_VALUE:      error="INVALID_VALUE";          break;
            case GL_OUT_OF_MEMORY:      error="OUT_OF_MEMORY";          break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
        }
        std::cout << "GL_" << error.c_str() <<" - " << file << ":" << line << std::endl;
        err = glGetError();
    }

    return;
}

void TestScene::start() 
{
    std::cout<<"TestScene Started";
    vertices = {
     0.5f,  0.5f, 0.0f,  
     0.5f, -0.5f, 0.0f,  
    -0.5f, -0.5f, 0.0f,  
    -0.5f,  0.5f, 0.0f    
    };
    unsigned int indices[] = { 
    0, 1, 3,   
    1, 2, 3    
    }; 
     glGenVertexArrays(1, &VAO); 
     glBindVertexArray(VAO);
     glGenBuffers(1, &VBO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO); 
     glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
     unsigned int EBO;
     glGenBuffers(1, &EBO);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
     glEnableVertexAttribArray(0); 
     program.subResources_.load();
     program.load();
     std::cout<<program.isLoaded();
}

void TestScene::update(float delta) 
{
    program.bind();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
