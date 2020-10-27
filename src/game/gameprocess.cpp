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
    currentScene = new TestScene(this);
    currentScene->start();
    Resources::External::Image testImage{"wall.jpg"};
    testImage.load();
    Color::ColorStruct temp = Color::fromInt(*((int32_t*)testImage.data()));
    std::cout<<(int)temp.r<<" "<<(int)temp.g<<" "<<(int)temp.b;
}
