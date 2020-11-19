#include "maze.hpp"

void mazeScene::start()
{
    menu->start();
    player.setFixedZ(true);
    glfwSetCursorPos(proc->getWnd(), window_w/2.0f, window_h/2.0f);
    maze.buildMaze();
    omm.init(maze, DrawableHolder(rootWallModel.get()), DrawableHolder(lineWallModel.get()),DrawableHolder(cornerWallModel.get()));
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
    view = player.getCamera().getViewMatrix();
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection(1);
    projection = glm::perspective(glm::radians(45.0f), (float)window_w/window_h, 0.1f, 100.0f);
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));
    
    for(int i=0;i<omm.height();i++)
        for(int j=0;j<omm.width();j++)
            if(auto t = omm.get(j,i))
                t->model.draw(program->getProgram());
    //lineWallModel->draw(program->getProgram());
    
    menu->draw();

    CheckGLError();
}

void mazeScene::physTick(float delta) 
{
    double xpos, ypos;
    glfwGetCursorPos(proc->getWnd(), &xpos, &ypos);

    player.mouseOffsetInput(-(window_w/2.0f-xpos)*delta*10, (window_h/2.0f-ypos)*delta*10);

    glfwSetCursorPos(proc->getWnd(), window_w/2.0f, window_h/2.0f);

    if(glfwGetKey(proc->getWnd(), GLFW_KEY_W)==GLFW_PRESS)
        player.moveStraight(delta*10);
    if(glfwGetKey(proc->getWnd(), GLFW_KEY_S)==GLFW_PRESS)
        player.moveStraight(-delta*10);
    if(glfwGetKey(proc->getWnd(), GLFW_KEY_D)==GLFW_PRESS)
        player.moveSideways(delta*10);
    if(glfwGetKey(proc->getWnd(), GLFW_KEY_A)==GLFW_PRESS)
        player.moveSideways(-delta*10);

    if(glfwGetKey(proc->getWnd(), GLFW_KEY_F)==GLFW_PRESS)
        player.setFixedZ(!player.getFixedZ());

    menu->debug_setDebugPlayerPos(player.getCamera().getPos().x,player.getCamera().getPos().z);
}

ResourcePack mazeScene::getResources()
{
    ResourcePack temp;
    temp.setResources(menu->getResources().getRes());
    temp.getRes().assign({cornerWallModel.get(), rootWallModel.get(),lineWallModel.get(), program.get()});
    return temp;
}

void mazeScene::initResources()
{
    menu = rm->createResource<>(MazeGui(window_w, window_h, rm),sceneName);
    cornerWallModel = rm->createResource(res::ogl::Model("data\\models\\cornerWall.obj"), sceneName, "cornerWallModel");
    rootWallModel = rm->createResource(res::ogl::Model("data\\models\\oneUnitWall.obj"), sceneName, "rootWallModel");
    lineWallModel = rm->createResource(res::ogl::Model("data\\models\\threeUnitWall.obj"), sceneName, "lineWallModel");
    program = rm->createResource(res::ogl::ShaderProgram("data\\shaders\\basic\\shader.vert", "data\\shaders\\basic\\shader.frag", "basicShader"), sceneName);
}

mazeScene::mazeScene(GameProcess* proc) : 
Scene(proc), maze(10,10)
{
    sceneName = "maze_scene";
    glfwGetWindowSize(proc->getWnd(), &window_w, &window_h);
}
