#include "maze.hpp"

void mazeScene::start()
{
    cam.moveStraight(-15);
    cam.moveSideways(-5);
    glfwSetCursorPos(proc->getWnd(), window_w/2.0f, window_h/2.0f);
}

void mazeScene::update(float delta)
{
    int state = glfwGetKey(proc->getWnd(), GLFW_KEY_ESCAPE);
    if(state == GLFW_PRESS)
        glfwSetWindowShouldClose(proc->getWnd(), true);
}

void mazeScene::onDraw(float delta)
{
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
    //tempTexture->bind(0);
    model->draw(program->getProgram());
    CheckGLError();
}

void mazeScene::physTick(float delta) 
{
    double xpos, ypos;
    glfwGetCursorPos(proc->getWnd(), &xpos, &ypos);

    cam.addRotation(-(window_w/2.0f-xpos)*delta*10, (window_h/2.0f-ypos)*delta*10);

    glfwSetCursorPos(proc->getWnd(), window_w/2.0f, window_h/2.0f);

    if(glfwGetKey(proc->getWnd(), GLFW_KEY_W)==GLFW_PRESS)
        cam.moveStraight(delta*10);
    if(glfwGetKey(proc->getWnd(), GLFW_KEY_S)==GLFW_PRESS)
        cam.moveStraight(-delta*10);
    if(glfwGetKey(proc->getWnd(), GLFW_KEY_D)==GLFW_PRESS)
        cam.moveSideways(delta*10);
    if(glfwGetKey(proc->getWnd(), GLFW_KEY_A)==GLFW_PRESS)
        cam.moveSideways(-delta*10);
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
