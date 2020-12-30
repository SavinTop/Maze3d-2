#include "maze.hpp"
#include "scenes/menu/menu.hpp"
#include "maze_things/utils/coloredMapGenerator.hpp"
#include "render/easyLineRender.hpp"

void mazeScene::start()
{
    player.setFixedZ(true);
    player.setPosition(glm::vec3(3, 0, 3));
    player.mouseOffsetInput(-240, 0);
    maze.buildMaze();
    omm.init(maze, DrawableHolder(rootWallModel.get()), DrawableHolder(lineWallModel.get()), DrawableHolder(cornerWallModel.get()));
    rth = RaycastingHandler(50, &omm);
    int maze_size = omm.width();
    floor.setParams(glm::vec2(maze_size * 8 - 6, maze_size * 8 - 6), {floorTexture, floorTextureNormal});
    floor.setPosition(glm::vec3(maze_size * 8 / 2.0 - 4, -3, maze_size * 8 / 2.0 - 4));
    floor.load();
    laserModel.setParams(glm::vec3(0.05,0.05,0.05));
    laserModel.load();

    calcShadows();

    auto settings = res::ogl::DefaultTextureInfo;
    settings.mag_filter = GL_NEAREST;
    settings.min_filter = GL_NEAREST;
    settings.wrap_s = GL_CLAMP_TO_EDGE;
    settings.wrap_t = GL_CLAMP_TO_EDGE;

    ColoredMapGenerator cmg;
    cmg.generateMap(maze);

    maze_texture.reset(new res::ogl::Texture(cmg.getImg(), res::ogl::TextureType::Diffuse, settings));
    maze_texture->load();

    menu->setMazeMap(maze_texture);
    menu->start();
    menu->setOkCallback(std::bind(&mazeScene::okClicked, this));
    glfwSetInputMode(proc->getWnd(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    proc->SetPause(true); //TODO

    for(int i=0;i<10;i++)
    {
        lasers[i].holder.setTarget((Drawable*)&laserModel);
        lasers[i].destroyed = true;
    }
}

void mazeScene::update(float delta)
{
    int state = glfwGetKey(proc->getWnd(), GLFW_KEY_ESCAPE);
    if (state == GLFW_PRESS)
    {
        goToMainMenu();
    }
}

void mazeScene::mouseMove(double xpos, double ypos)
{
    menu->mouseInput(xpos,ypos,false);
    if (proc->GetPause())
        return;
    const float SENSITIVTY = 0.07f;
    glfwSetCursorPos(proc->getWnd(), window_w / 2, window_h / 2);
    player.mouseOffsetInput((xpos - window_w / 2.0f) * SENSITIVTY, (window_h / 2.0f - ypos) * SENSITIVTY);
}

void mazeScene::mouseDown(double xpos, double ypos, int mb, int action) 
{
    bool lm = mb==GLFW_MOUSE_BUTTON_LEFT && action==GLFW_RELEASE;
    if(lm)
    {
        menu->mouseInput(xpos,ypos,lm);
        if(cheatCode_h.getSettings().doom)
        shotLaser(player.getCamera().getPos()+player.getCamera().getFront(), player.getCamera().getFront(), 100);
    }
        menu->mouseInput(xpos,ypos,false);  
}

void mazeScene::charInput(unsigned int character) 
{
    if(!timed)
    cheatCode_h.charInput(character);
}

void mazeScene::okClicked() 
{
    glfwSetInputMode(proc->getWnd(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    proc->SetPause(false);
    menu->currentWindow = &menu->timer;
    last_time = glfwGetTime();
    glfwSetCursorPos(proc->getWnd(), window_w / 2.0f, window_h / 2.0f);
}

void mazeScene::calcShadows()
{
    glCullFace(GL_FRONT);
    shadow_h.gl_init(maze_size_, 10);
    shadowProgram->bind();
    unsigned int lsm_id = shadowProgram->getUniformLocation("lightSpaceMatrix");

    float width = maze_size_ * 6;
    float height = maze_size_ * 4;

    glm::mat4 lightProjection = glm::ortho(-width, width, -height, height, 1.0f, 1000.0f);
     glm::mat4 lightView = glm::lookAt(lightPosition * (float)(maze_size_ / 5),
                                       floor.getPosition(),
                                       glm::vec3(0.0f, 1.0f, 0.0f));
    lightSpaceMatrix = lightProjection * lightView;
    glUniformMatrix4fv(lsm_id, 1, false, glm::value_ptr(lightSpaceMatrix));
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    shadow_h.begin();
    for (int i = 0; i < omm.height(); i++)
        for (int j = 0; j < omm.width(); j++)
            omm.get(j, i)->model.draw(shadowProgram->getProgram());

    floor.draw(shadowProgram->getProgram());
    shadow_h.end(window_w, window_h);
    CheckGLError();
    glCullFace(GL_BACK);
}

void mazeScene::Lvld0ne_endless() 
{
    auto next = new LoadingScene(proc, new mazeScene(proc, maze_size_+5));
    next->initResources();
    auto temp = next->getResources();
    for (auto &el : temp.getRes())
    {
        el->subResources_.load();
        el->load();
    }
    proc->ChangeScene(next);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void mazeScene::Lvld0ne_timed() 
{
    goToMainMenu();
    std::cout<<"maze "<<maze_size_<<" dur "<<timer<<std::endl;
    dh_test.update(maze_size_/5-1, timer);
    dh_test.save();
}

void mazeScene::goToMainMenu() 
{
    glfwSetInputMode(proc->getWnd(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    auto next = new LoadingScene(proc, new Menu(proc));
    next->initResources();
    auto temp = next->getResources();
    for (auto &el : temp.getRes())
    {
        el->subResources_.load();
        el->load();
    }
    proc->ChangeScene(next);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

mazeScene::mazeScene(GameProcess *proc, int maze_size, bool timed) : Scene(proc), maze(maze_size, maze_size)
{
    sceneName = timed?"maze_scene_timed":"maze_scene_endless";
    glfwGetWindowSize(proc->getWnd(), &window_w, &window_h);
    glfwSetInputMode(proc->getWnd(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    fov = 60;
    maze_size_ = maze_size;
    this->timed = timed;
    timer = 0;
    dh_test.load();
}

mazeScene::~mazeScene()
{
    maze_texture->unload();
    shadow_h.clear();
    floor.unload();
    laserModel.unload();
}