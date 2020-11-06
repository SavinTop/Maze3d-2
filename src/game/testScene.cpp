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
    
}


void TestScene::update(float delta) 
{
    int state = glfwGetKey(proc_->getWnd(), GLFW_KEY_ESCAPE);
    if(state == GLFW_PRESS)
        glfwSetWindowShouldClose(proc_->getWnd(), true);
}

void TestScene::onDraw(float delta) 
{
    glClear(GL_COLOR_BUFFER_BIT);
    program->bind();
    unsigned viewId = program->getUniformLocation("view");
    unsigned projectionId = program->getUniformLocation("projection");
    unsigned modelId = program->getUniformLocation("model");
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
    glm::mat4 projection(1); 
    projection = glm::perspective(glm::radians(45.0f), 1.778f, 0.1f, 100.0f);
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));
    //mesh->draw(program);
    glBindTexture(GL_TEXTURE_2D, 0);
    testPlane->draw(*program);
    CheckGLError();
}

ResourcePack TestScene::getResources() 
{
    return ResourcePack({program, testPlane, test});
}

void TestScene::initResources() 
{
    program = proc_->rm->createResource<>(res::ogl::ShaderProgram("data/shaders/basic/shader.vert","data/shaders/basic/shader.frag","basic program2"));
    test = proc_->rm->createResource<>(res::ogl::Texture("wall.jpg"));
    testPlane = proc_->rm->createResource<>(res::ogl::Plane(glm::vec3(), glm::vec2(2,2), {test}));
}


TestScene::TestScene(GameProcess* proc)
    :Scene(proc)
{
    
}
