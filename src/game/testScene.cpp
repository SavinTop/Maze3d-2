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

    auto* tex = proc_->rm->createResource<>(res::ogl::Texture{"wall.jpg"});
    tex->getImage().load();
    tex->load();

    std::vector<Containers::Vertex> vertices = {
        Containers::Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec3(), glm::vec2(0,0)),
        Containers::Vertex(glm::vec3( 0.5, -0.5, 0.0), glm::vec3(), glm::vec2(1,0)),
        Containers::Vertex(glm::vec3( 0.5,  0.5, 0.0), glm::vec3(), glm::vec2(1,1)),
        Containers::Vertex(glm::vec3(-0.5,  0.5, 0.0), glm::vec3(), glm::vec2(0,1))
    };

    std::vector<unsigned> indices = {0,1,2 , 2,0,3};

    Containers::Mesh mesh_C{vertices, indices, {tex}};

    mesh = proc_->rm->createResource<>(res::ogl::Mesh(mesh_C));

    mesh->load();
    mesh->setRotation(glm::vec3(glm::radians(-45.0f),0,0));
    mesh->setScale(glm::vec3(1));
}


void TestScene::update(float delta) 
{
    program.bind();
    unsigned viewId = program.getUniformLocation("view");
    unsigned projectionId = program.getUniformLocation("projection");
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
    glm::mat4 projection(1); 
    projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));
    mesh->draw(program);
    CheckGLError();
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
