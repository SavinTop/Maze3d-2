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
    Camera cam;
    cam.moveStraight(-15);
    cam.moveSideways(-6);
    cam.addRotation(45,0);
    program->bind();
    unsigned viewId = program->getUniformLocation("view");
    unsigned projectionId = program->getUniformLocation("projection");
    unsigned imageId = program->getUniformLocation("texture_diffuse1");
    glm::mat4 view = glm::mat4(1.0f);
    view = cam.getViewMatrix();
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection(1);
    projection = glm::perspective(glm::radians(45.0f), (float)window_w/window_h, 0.1f, 100.0f);
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));
    tempTexture->bind(0);
    model->draw(program->getProgram());
    CheckGLError();
}

ResourcePack mazeScene::getResources()
{
    return ResourcePack({model.get(), program.get(), tempTexture.get()});
}

void mazeScene::initResources()
{
    model = rm->createResource(res::ogl::Model("data\\models\\threeUnitWall.obj"), sceneName, "test Model");
    program = rm->createResource(res::ogl::ShaderProgram("data\\shaders\\basic\\shader.vert", "data\\shaders\\basic\\shader.frag", "basicShader"), sceneName);
    tempTexture = rm->createResource(res::ogl::Texture("data\\models\\Wall_Stone_017_BaseColor.jpg"));
}

mazeScene::mazeScene(GameProcess* proc) : Scene(proc)
{
    sceneName = "maze_scene";
    glfwGetWindowSize(proc->getWnd(), &window_w, &window_h);
}
