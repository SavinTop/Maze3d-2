#include "gameprocess.hpp"


void GameProcess::SetCurrentScene(Scene* scene) 
{
    currentScene = scene;
    scene->getResources().load();
    currentScene->Start();
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
        currentScene->Update(curr-last);
        last = curr;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

GameProcess::GameProcess(GLFWwindow* wnd) 
: window(wnd)
{
    currentScene = new TestScene(this);
    currentScene->Start();
}
