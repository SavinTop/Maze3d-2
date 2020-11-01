#include "gameprocess.hpp"
#include "baseTypes/resources/external/TextFile.hpp"
#include "baseTypes/resources/external/Image.hpp"
#include "baseTypes/containers/Image.hpp"
#include "baseTypes/color.hpp"

void GameProcess::SetCurrentScene(Scene* scene) 
{
    currentScene = scene;
    //scene->getResources().load();
    currentScene->start();
}

void GameProcess::Init() 
{
    
}

void GameProcess::Start() 
{
    double last = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        double curr = glfwGetTime();
        currentScene->update(curr-last);
        last = curr;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

GameProcess::GameProcess(GLFWwindow* wnd) 
: window(wnd)
{
    rm = new ResourceManager();
    currentScene = new TestScene(this);
    currentScene->start();
}
