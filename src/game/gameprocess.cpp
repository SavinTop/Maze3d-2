#include "gameprocess.hpp"
#include "baseTypes/resources/external/TextFile.hpp"
#include "baseTypes/resources/external/Image.hpp"
#include "baseTypes/containers/Image.hpp"
#include "baseTypes/color.hpp"
#include "testScene.hpp"
#include "scenes/loadingScenes/startLoadingScene/startLoadingScene.hpp"

void GameProcess::SetCurrentScene(Scene* scene) 
{
    asm("nop");
    delete currentScene;
    currentScene = scene;
    currentScene->start();
}

void GameProcess::Init() 
{
    
}

void GameProcess::Start() 
{
    double lastDraw = glfwGetTime();
    double lastUpdate = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        double currUpdate = glfwGetTime();
        currentScene->update(currUpdate-lastUpdate);
        lastUpdate = currUpdate;

        double currDraw = glfwGetTime();
        currentScene->onDraw(currDraw-lastDraw);
        lastDraw = currDraw;

        glfwSwapBuffers(window);
        glfwPollEvents();
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
}
