#include "menu.hpp"

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

void Menu::start() 
{
    button = Button{idle.get(), active.get()};
    glfwGetWindowSize(proc->getWnd(), &window_w, &window_h);
    fbox = FullscreenBox(window_w, window_h);
    button.setParent(&fbox);
    button.setSize(0.3f,0.09f);
    button.setPosition(0.0f,-0.5f);
}

void Menu::update(float delta) 
{
    int state = glfwGetKey(proc->getWnd(), GLFW_KEY_ESCAPE);
    if(state == GLFW_PRESS)
        glfwSetWindowShouldClose(proc->getWnd(), true);

    double x,y;

    glfwGetCursorPos(proc->getWnd(),&x,&y);

    this->fbox.__mouseMove(x,window_h-y);
}

void Menu::onDraw(float delta) 
{
    glClear(GL_COLOR_BUFFER_BIT);
    program->bind();
    unsigned viewId = program->getUniformLocation("view");
    unsigned projectionId = program->getUniformLocation("projection");
    unsigned modelId = program->getUniformLocation("model");
    unsigned colorId = program->getUniformLocation("color");
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
    glm::mat4 projection(1); 
    projection = glm::ortho(0.0f,(float)window_w,0.0f,(float)window_h,0.1f,100.0f);
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));
    float color[] = {0,1,0,1};
    glUniform4fv(colorId, 1, color);
    //mesh->draw(program);
    button.draw(*program);
    
    
    CheckGLError();
}

ResourcePack Menu::getResources() 
{
    return ResourcePack({program.get(), active.get(), idle.get()});
}

void Menu::initResources() 
{
    program = rm->createResource<>(res::ogl::ShaderProgram("data/shaders/basic/shader.vert","data/shaders/basic/shader.frag","basic program2"),sceneName);
    active = rm->createResource<>(res::ogl::Texture("data\\scenes\\mainMenu\\sprites\\buttons\\exit_active.png"),sceneName);
    idle = rm->createResource<>(res::ogl::Texture("data\\scenes\\mainMenu\\sprites\\buttons\\exit_idle.png"),sceneName);
    //testPlane = rm->createResource<>(res::ogl::Plane(glm::vec3(200,200,0), glm::vec2(200,200), {test.get()}),sceneName);
}

void Menu::exitClicked() 
{
    glfwSetWindowShouldClose(proc->getWnd(), true);
}


Menu::Menu(GameProcess* proc)
    :Scene(proc)
{
    rm = proc->rm;
    sceneName = "test_scene";
}
