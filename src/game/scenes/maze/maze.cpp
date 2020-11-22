#include "maze.hpp"
#include "scenes/menu/menu.hpp"

static void printMazeAndPlayer(MazeBuilder &maze, glm::vec2 playerPos);

void mazeScene::start()
{
    menu->start();
    player.setFixedZ(true);
    player.setPosition(glm::vec3(3, 0, 3));
    player.mouseOffsetInput(-240, 0);
    floor.setParams(glm::vec2(50 * 8, 50 * 8), {floorTexture, floorTextureNormal});
    floor.setPosition(glm::vec3(50 * 8 / 2.0, -3, 50 * 8 / 2.0));
    floor.load();
    glfwSetCursorPos(proc->getWnd(), window_w / 2.0f, window_h / 2.0f);
    maze.buildMaze();
    omm.init(maze, DrawableHolder(rootWallModel.get()), DrawableHolder(lineWallModel.get()), DrawableHolder(cornerWallModel.get()));

    //TODO delete
    glGenFramebuffers(1, &depthMapFBO);
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    tempGenerateShadowMap();
}

void mazeScene::update(float delta)
{
    int state = glfwGetKey(proc->getWnd(), GLFW_KEY_ESCAPE);
    if (state == GLFW_PRESS)
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
    }
}

void mazeScene::onDraw(float delta)
{
    program->bind();
    unsigned viewId = program->getUniformLocation("view");
    unsigned projectionId = program->getUniformLocation("projection");
    unsigned lightDirId = program->getUniformLocation("lightDir");
    glm::mat4 view = glm::mat4(1.0f);
    view = player.getCamera().getViewMatrix();

    glm::mat4 projection(1);
    projection = glm::perspective(glm::radians(fov), (float)window_w / window_h, 0.1f, 100.0f);
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));

    auto playerPos = player.getCamera().getPos() / 8.0f;

    unsigned int lightSpaceMatrixLocation = program->getUniformLocation("lightSpaceMatrix");
    CheckGLError();
    glUniformMatrix4fv(lightSpaceMatrixLocation, 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
    CheckGLError();
    glUniform1i(program->getUniformLocation("shadowMap"), 5);
    CheckGLError();
    glActiveTexture(GL_TEXTURE5);
    CheckGLError();
    glBindTexture(GL_TEXTURE_2D, depthMap);
    CheckGLError();

    glm::vec3 sunPos{-0.462, 0.376, -0.802};
    glUniform3fv(lightDirId, 1, glm::value_ptr(sunPos));
    //glUniform3fv(lightId, 1, glm::value_ptr(player.getCamera().getPos()));

    glUniform3fv(program->getUniformLocation("viewPos"), 1, glm::value_ptr(player.getCamera().getPos()));

    for (int i = 0; i < omm.height(); i++)
        for (int j = 0; j < omm.width(); j++)
            if (auto t = omm.get(j, i))
                t->model.draw(program->getProgram());

    floor.draw(program->getProgram());

    glDepthFunc(GL_LEQUAL);
    skyboxProgram->bind();
    glUniform1i(skyboxProgram->getUniformLocation("skybox"), 0);
    viewId = skyboxProgram->getUniformLocation("view");
    projectionId = skyboxProgram->getUniformLocation("projection");
    view = glm::mat4(glm::mat3(player.getCamera().getViewMatrix()));
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));
    cmo->draw(skyboxProgram->getProgram());
    glDepthFunc(GL_LESS);
    //menu->draw();
    CheckGLError();
}

void mazeScene::physTick(float delta)
{
    const float collBox = 0.2;

    glm::vec3 lastPlayerPos = player.getCamera().getPos();

    float playerSpeed = 10;

    if (glfwGetKey(proc->getWnd(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        playerSpeed *= 2;
        fov = glm::min(70.0f, fov + 10 * delta);
    }
    else
        fov = glm::max(60.0f, fov - 10 * delta);

    if (glfwGetKey(proc->getWnd(), GLFW_KEY_W) == GLFW_PRESS)
        player.moveStraight(delta * playerSpeed);
    if (glfwGetKey(proc->getWnd(), GLFW_KEY_S) == GLFW_PRESS)
        player.moveStraight(-delta * playerSpeed);
    if (glfwGetKey(proc->getWnd(), GLFW_KEY_D) == GLFW_PRESS)
        player.moveSideways(delta * playerSpeed);
    if (glfwGetKey(proc->getWnd(), GLFW_KEY_A) == GLFW_PRESS)
        player.moveSideways(-delta * playerSpeed);

    if (glfwGetKey(proc->getWnd(), GLFW_KEY_F) == GLFW_PRESS)
        player.setFixedZ(!player.getFixedZ());

    auto getPointCollBox = [&collBox](glm::vec3 pos) {
        return glm::vec4{pos.x - collBox, pos.z - collBox, pos.x + collBox, pos.z + collBox};
    };

    glm::vec3 playerPos = player.getCamera().getPos();
    menu->debug_setDebugPlayerPos(playerPos.x, playerPos.z);
    glm::ivec2 sector(playerPos.x / 8.0f, playerPos.z / 8.0f);
    glm::vec3 tempPos = playerPos;
    auto t = checkCollision(omm, sector, getPointCollBox(tempPos));

    if (t)
    {
        auto fixedX = tempPos * glm::vec3(0, 1, 1) + glm::vec3(lastPlayerPos.x, 0, 0);
        auto tx = checkCollision(omm, sector, getPointCollBox(fixedX));
        auto fixedY = tempPos * glm::vec3(1, 1, 0) + glm::vec3(0, 0, lastPlayerPos.z);
        auto ty = checkCollision(omm, sector, getPointCollBox(fixedY));
        if (!tx || ty)
        {
            tempPos.x = fixedX.x;
        }
        if (!ty || tx)
        {
            tempPos.z = fixedY.z;
        }

        player.setPosition(tempPos);
    }
}

void mazeScene::mouseMove(double xpos, double ypos)
{
    const float SENSITIVTY = 0.07f;
    glfwSetCursorPos(proc->getWnd(), window_w / 2, window_h / 2);
    player.mouseOffsetInput((xpos - window_w / 2.0f) * SENSITIVTY, (window_h / 2.0f - ypos) * SENSITIVTY);
}

void mazeScene::tempGenerateShadowMap()
{
    float near_plane = 1.0f, far_plane = 500.0f;
    glm::mat4 lightProjection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(glm::vec3(-10.0f, 7.0f, -10.0f),
                                      glm::vec3(50 * 8 / 2.0, -3.0f, 50 * 8 / 2.0),
                                      glm::vec3(0.0f, 1.0f, 0.0f));
    lightSpaceMatrix = lightProjection * lightView;
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    shadowProgram->bind();
    unsigned int lightSpaceMatrixLocation = shadowProgram->getUniformLocation("lightSpaceMatrix");
    
    glUniformMatrix4fv(lightSpaceMatrixLocation, 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    for (int i = 0; i < omm.height(); i++)
        for (int j = 0; j < omm.width(); j++)
            if (auto t = omm.get(j, i))
                t->model.draw(shadowProgram->getProgram());

    floor.draw(shadowProgram->getProgram());
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, window_w, window_h);
}

mazeScene::mazeScene(GameProcess *proc) : Scene(proc), maze(20, 20)
{
    sceneName = "maze_scene";
    glfwGetWindowSize(proc->getWnd(), &window_w, &window_h);
    glfwSetInputMode(proc->getWnd(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    fov = 45;
}