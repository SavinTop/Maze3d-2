#include "maze.hpp"

void mazeScene::start()
{
    menu->start();
    player.setFixedZ(true);
    player.setPosition(glm::vec3(3,0,3));
    player.mouseOffsetInput(-240, 0);
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
    glm::mat4 view = glm::mat4(1.0f);
    view = player.getCamera().getViewMatrix();
    glm::mat4 projection(1);
    projection = glm::perspective(glm::radians(45.0f), (float)window_w/window_h, 0.1f, 100.0f);
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));

    // for(int i=0;i<omm.height();i++)
    //     for(int j=0;j<omm.width();j++)
    //         if(auto t = omm.get(j,i))
    //             t->model.draw(program->getProgram());

    auto playerPos = player.getCamera().getPos()/8.0f;

    for(int i=playerPos.z-5;i<=playerPos.z+5;i++)
        for(int j=playerPos.x-5;j<=playerPos.x+5;j++)
            if(auto t = omm.get(j,i))
                t->model.draw(program->getProgram());

    menu->draw();
    CheckGLError();
}

void mazeScene::physTick(float delta) 
{
    const float collBox = 0.2;

    double xpos, ypos;
    glfwGetCursorPos(proc->getWnd(), &xpos, &ypos);

    glm::vec2 mouseInputOffsets{-(window_w/2.0f-xpos)*delta*10, (window_h/2.0f-ypos)*delta*10};

    player.mouseOffsetInput(mouseInputOffsets.x, mouseInputOffsets.y);

    glfwSetCursorPos(proc->getWnd(), window_w/2.0f, window_h/2.0f);

    glm::vec3 lastPlayerPos = player.getCamera().getPos();

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

    auto getPointCollBox = [&collBox](glm::vec3 pos){
        return glm::vec4{ pos.x - collBox, pos.z - collBox,pos.x + collBox, pos.z + collBox };
    };

    glm::vec3 playerPos = player.getCamera().getPos();
    menu->debug_setDebugPlayerPos(playerPos.x,playerPos.z);
    glm::ivec2 sector(playerPos.x/8.0f, playerPos.z/8.0f);
    glm::vec3 tempPos = playerPos;
    auto t = checkCollision(omm, sector, getPointCollBox(tempPos));
    
    if(t){
        auto fixedX = tempPos*glm::vec3(0,1,1)+glm::vec3(lastPlayerPos.x,0,0);
        auto tx = checkCollision(omm, sector, getPointCollBox(fixedX));
        auto fixedY = tempPos*glm::vec3(1,1,0)+glm::vec3(0,0,lastPlayerPos.z);
        auto ty = checkCollision(omm, sector, getPointCollBox(fixedY));
        if(!tx || ty){
            tempPos.x = fixedX.x; 
            std::cout<<"x fixed\n";
        }
        if(!ty || tx){
            tempPos.z = fixedY.z;
            std::cout<<"y fixed\n";
        }
        
        player.setPosition(tempPos);
    }
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

mazeObject* mazeScene::checkCollision(ObjectMazeMap& omm, glm::ivec2 sector, glm::vec4 playerRect) 
{
    for (int y = sector.y - 1; y <= sector.y + 1; y++)
		for (int x = sector.x - 1; x <= sector.x + 1; x++)
		{
			mazeObject* temp = omm.get(x, y);
			if (temp)
			{
				auto t = *temp;
				auto firstColl = coll(playerRect, t.fw);
				if (firstColl) return temp;
				if (t.wt == Corner)
				{
					auto secondColl = coll(playerRect, t.sw);
					if (secondColl) return temp;
				}
			}
		}
	return nullptr;
}

mazeScene::mazeScene(GameProcess* proc) : 
Scene(proc), maze(10,10)
{
    sceneName = "maze_scene";
    glfwGetWindowSize(proc->getWnd(), &window_w, &window_h);
}
