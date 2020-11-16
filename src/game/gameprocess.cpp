#include "gameprocess.hpp"
#include "baseTypes/resources/external/TextFile.hpp"
#include "baseTypes/resources/external/Image.hpp"
#include "baseTypes/containers/Image.hpp"
#include "baseTypes/color.hpp"
#include "scenes/loadingScenes/startLoadingScene/startLoadingScene.hpp"

void GameProcess::SetCurrentScene(Scene* scene) 
{
    delete currentScene;
    currentScene = scene;
    currentScene->start();
    std::cout<<"current scene set on: "<<currentScene->getName()<<"\n";
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
        glClear(GL_COLOR_BUFFER_BIT);
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
