#include "gameprocess.hpp"
#include "baseTypes/resources/external/TextFile.hpp"
#include "baseTypes/resources/external/Image.hpp"
#include "baseTypes/containers/Image.hpp"
#include "baseTypes/color.hpp"
#include "scenes/loadingScenes/startLoadingScene/startLoadingScene.hpp"

const int maxFps = 120;
const int PPS = 100;

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
    
}

void GameProcess::Start() 
{
    double lastDraw = glfwGetTime();
    double lastUpdate = glfwGetTime();
    double lastPhys = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        double currUpdate = glfwGetTime();
        
        currentScene->update(currUpdate-lastUpdate);
        lastUpdate = currUpdate;

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

GameProcess::GameProcess(GLFWwindow* wnd) 
: window(wnd)
{
    rm = new ResourceManager();
    currentScene = new StartLoadingScene(this);
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
