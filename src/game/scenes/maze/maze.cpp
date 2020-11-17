#include "maze.hpp"

void mazeScene::start()
{

}

void mazeScene::update(float delta)
{
    //std::cout<<model->resName_<<"\n";
    __asm("nop");
}

void mazeScene::onDraw(float delta)
{
    program->bind();
    unsigned viewId = program->getUniformLocation("view");
    unsigned projectionId = program->getUniformLocation("projection");
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0,0,3));
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection(1);
    projection = glm::perspective(glm::radians(45.0f), (float)window_w/window_h, 0.1f, 100.0f);
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));
    model->draw(program->getProgram());
}

ResourcePack mazeScene::getResources()
{
    return ResourcePack({model.get(), program.get()});
}

void mazeScene::initResources()
{
    model = rm->createResource(res::ogl::Model("temp\\backpack.obj"), sceneName, "test Model");
    program = rm->createResource(res::ogl::ShaderProgram("data\\shaders\\basic.vert", "data\\shaders\\basic.frag", "basicShader"), sceneName);
}

mazeScene::mazeScene(GameProcess* proc) : Scene(proc)
{
    sceneName = "maze_scene";
    glfwGetWindowSize(proc->getWnd(), &window_w, &window_h);
}
