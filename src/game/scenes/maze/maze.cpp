#include "maze.hpp"
#include "scenes/menu/menu.hpp"
#include "maze_things/utils/coloredMapGenerator.hpp"
#include "render/easyLineRender.hpp"

static void printMazeAndPlayer(MazeBuilder &maze, glm::vec2 playerPos);

void mazeScene::start()
{
    player.setFixedZ(true);
    player.setPosition(glm::vec3(3, 0, 3));
    player.mouseOffsetInput(-240, 0);
    glfwSetCursorPos(proc->getWnd(), window_w / 2.0f, window_h / 2.0f);
    maze.buildMaze();
    omm.init(maze, DrawableHolder(rootWallModel.get()), DrawableHolder(lineWallModel.get()), DrawableHolder(cornerWallModel.get()));
    rth = RaycastingHandler(50,&omm);
    int maze_size = omm.width();
    floor.setParams(glm::vec2(maze_size * 8-6+300, maze_size * 8-6+300), {floorTexture, floorTextureNormal});
    floor.setPosition(glm::vec3(maze_size * 8 / 2.0-4, -3, maze_size * 8 / 2.0-4));
    floor.load();
     //MazeMapGenerator mmg{maze};
    
     //std::vector<unsigned char> image_data;
     //image_data.insert(image_data.begin(),mmg.getData(),mmg.getData()+mmg.getHeight()*mmg.getWidth()*3);

     //Containers::Image temp;
     //temp.setData(image_data, mmg.getWidth(), mmg.getHeight(), 3);

    calcShadows();

    auto settings = res::ogl::DefaultTextureInfo;
    settings.mag_filter = GL_NEAREST;
    settings.min_filter = GL_NEAREST;
    settings.wrap_s = GL_CLAMP_TO_EDGE;
    settings.wrap_t = GL_CLAMP_TO_EDGE;

    ColoredMapGenerator cmg;
    cmg.generateMap(maze);

    maze_texture.reset(new res::ogl::Texture(cmg.getImg(),res::ogl::TextureType::Diffuse, settings));
    maze_texture->load();
    
    menu->setMazeMap(maze_texture);
    menu->start();
    proc->SetPause(false);//TODO
    //std::cout<<"TEXSHADOW ___ ___ __ ___ "<<maze_texture->getId()<<std::endl;
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
    unsigned lightspacematrixid = program->getUniformLocation("lightSpaceMatrix");
    unsigned shadowMapid = program->getUniformLocation("shadowMap");
    glm::mat4 view = glm::mat4(1.0f);
    view = player.getCamera().getViewMatrix();
    glm::mat4 projection(1);
    projection = glm::perspective(glm::radians(fov), (float)window_w / window_h, 0.1f, 600.0f);
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));

    auto playerPos = player.getCamera().getPos() / 8.0f;
    CheckGLError();

    glm::vec3 lightDir = glm::normalize(lightPosition-floor.getPosition());
    glUniform3fv(lightDirId, 1, glm::value_ptr(lightDir));

    glUniform3fv(program->getUniformLocation("viewPos"), 1, glm::value_ptr(player.getCamera().getPos()));

    glUniform1i(shadowMapid, 5);
    glActiveTexture(GL_TEXTURE0+5);
    glBindTexture(GL_TEXTURE_2D, shadow_h.depthMapTex_);

    glUniformMatrix4fv(lightspacematrixid, 1, false, glm::value_ptr(lightSpaceMatrix));

    glm::vec2 real_pp{player.getCamera().getPos().x,player.getCamera().getPos().z};
    float angle = glm::radians(player.getCamera().Yaw);

    rth.recalculate(glm::radians(fov), real_pp, angle);
    
    for(auto& el:rth.getCollidedSectors())
    {
        const int sector_size_plus = 2;
        const int sector_size_minus = 2;
        glm::ivec2 sector{el.first, el.second};
        for(int i=sector.y-sector_size_minus;i<=sector.y+sector_size_plus;i++)
                for(int j=sector.x-sector_size_minus;j<=sector.x+sector_size_plus;j++)
                if(auto t = omm.get(j,i))
                {
                    t->model.draw(program->getProgram());
                }
        
    }       

    floor.draw(program->getProgram());
    
    glDepthFunc(GL_LEQUAL);
    skyboxProgram->bind();
    glUniform1i(skyboxProgram->getUniformLocation("skybox"), 0);
    viewId = skyboxProgram->getUniformLocation("view");
    projectionId = skyboxProgram->getUniformLocation("projection");
    view = glm::mat4(glm::mat3(player.getCamera().getViewMatrix()));
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));
    glBindTexture(GL_TEXTURE_2D, shadow_h.depthMapTex_);
    cmo->draw(skyboxProgram->getProgram());
    glDepthFunc(GL_LESS);
    //menu->draw();
    
    depthMapProgram->bind();
    drawBasicTexturedRect(glm::vec4(-0.5,-0.5,0.3,0.3*(float)window_w/window_h), shadow_h.depthMapTex_, depthMapProgram->getProgram());
    //drawBasicTexturedRect(glm::vec4(0,0,1.0,1.0), maze_texture->getId(), depthMapProgram->getProgram());
    
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
    glm::ivec2 sector(playerPos.x / 8.0f, playerPos.z / 8.0f);
    menu->debug_setDebugPlayerPos(playerPos.x, playerPos.y);
    glm::vec3 tempPos = playerPos;
    auto t = checkCollision(omm, sector, getPointCollBox(tempPos));

    if (t && playerPos.y<4)
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
    if(proc->GetPause()) return;
    const float SENSITIVTY = 0.07f;
    glfwSetCursorPos(proc->getWnd(), window_w / 2, window_h / 2);
    player.mouseOffsetInput((xpos - window_w / 2.0f) * SENSITIVTY, (window_h / 2.0f - ypos) * SENSITIVTY);
}

void mazeScene::calcShadows() 
{
    glCullFace(GL_FRONT);
    shadow_h.gl_init(maze_size_, 20);
    shadowProgram->bind();
    unsigned int lsm_id = shadowProgram->getUniformLocation("lightSpaceMatrix");

    float width = maze_size_*6;
    float height = maze_size_*4;

    glm::mat4 lightProjection = glm::ortho(-width, width, -height, height, 1.0f, 500.0f);
    glm::mat4 lightView = glm::lookAt(lightPosition, 
                                  floor.getPosition(), 
                                  glm::vec3( 0.0f, 1.0f,  0.0f)); 
    lightSpaceMatrix = lightProjection * lightView; 
    glUniformMatrix4fv(lsm_id, 1, false, glm::value_ptr(lightSpaceMatrix));
    shadow_h.begin();
    for(int i=0;i<omm.height();i++)
        for(int j=0;j<omm.width();j++)
            omm.get(j,i)->model.draw(shadowProgram->getProgram());


    floor.draw(shadowProgram->getProgram());
    shadow_h.end(window_w, window_h);
    CheckGLError();
    glCullFace(GL_BACK);
}

mazeScene::mazeScene(GameProcess *proc, int maze_size) : 
Scene(proc), maze(maze_size, maze_size)
{
    sceneName = "maze_scene";
    glfwGetWindowSize(proc->getWnd(), &window_w, &window_h);
    glfwSetInputMode(proc->getWnd(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    fov = 45;
    maze_size_ = maze_size;
}

mazeScene::~mazeScene() 
{
    maze_texture->unload();
}