#include "gameprocess.hpp"
#include "baseTypes/resources/external/TextFile.hpp"
#include "baseTypes/resources/external/Image.hpp"
#include "baseTypes/containers/Image.hpp"
#include "baseTypes/color.hpp"
#include "scenes/loadingScenes/LoadingScene.hpp"
#include "scenes/menu/menu.hpp"

const int maxFps = 120;
const int PPS = 100;
const int UPS = 120;

void GameProcess::SetCurrentScene(Scene* scene) 
{
    delete currentScene;
    currentScene = scene;
    currentScene->start();
    std::cout<<"current scene set on: "<<currentScene->getName()<<"\n";
}

void GameProcess::ChangeScene(Scene* scene) 
{
    nextScene = scene;
}

void GameProcess::Init() 
{
    rm = new ResourceManager();
    currentScene = new LoadingScene(this, new Menu(this));
    currentScene->initResources();
    auto temp = currentScene->getResources();
    for(auto& el:temp.getRes())
    {
        el->subResources_.load();
        el->load();
    }
    currentScene->start();
    nextScene = nullptr;
}

void GameProcess::Start() 
{
    double lastDraw = glfwGetTime();
    double lastUpdate = glfwGetTime();
    double lastPhys = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        double currUpdate = glfwGetTime();
        if(currUpdate-lastUpdate>1.0f/UPS){
        currentScene->update(currUpdate-lastUpdate);
        lastUpdate = currUpdate;
        }

        double currPhys = glfwGetTime();
        if(currPhys-lastPhys>1.0f/PPS){
            currentScene->physTick(currPhys-lastPhys);
            lastPhys = currPhys;
        }

        double currDraw = glfwGetTime();
        if(currDraw-lastDraw>1.0f/maxFps){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        currentScene->onDraw(currDraw-lastDraw);
        lastDraw = currDraw;
        glfwSwapBuffers(window);
        }

        glfwPollEvents();
        if(nextScene){
            SetCurrentScene(nextScene);
            nextScene = nullptr;
        }
    }
}

GLFWwindow* GameProcess::getWnd() 
{
    return window;
}

void GameProcess::cursor_position_callback(double xpos, double ypos) 
{
    if(currentScene)
        currentScene->mouseMove(xpos,ypos);
}

GameProcess::GameProcess(GLFWwindow* wnd) 
: window(wnd)
{
    
}
