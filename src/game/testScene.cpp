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
    std::cout<<"TestScene Started"<<std::endl; 
     program.subResources_.load();
     program.load();

     std::cout<<program.isLoaded();
    std::cout<<"loading ended"<<std::endl;
}


void TestScene::update(float delta) 
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

ResourcePack TestScene::getResources() 
{
    return ResourcePack({&program});
}


TestScene::TestScene(GameProcess* proc)
    :Scene(proc),
    program("shader.vert","shader.frag","basic program")
{
    res::ogl::Texture* testTexture = proc->rm->createResource<res::ogl::Texture>(res::ogl::Texture("wall.jpg", res::ogl::TextureType::Diffuse, res::ogl::DefaultTextureInfo, "wallTexture"), LifeTime::Permanent);
    auto temp = proc->rm->createResource<res::ex::Image>(res::ex::Image("wall.jpg"));
    temp->load();
    program.load();
}
