#include "gameprocess.hpp"
#include "baseTypes/resources/external/TextFile.hpp"
#include "baseTypes/resources/external/Image.hpp"
#include "baseTypes/containers/Image.hpp"
#include "baseTypes/color.hpp"
#include "scenes/loadingScenes/LoadingScene.hpp"
#include "scenes/menu/menu.hpp"
#include "game/scenes/belarus/belarusScene.hpp"

const int maxFps = 200;
const int PPS = 100;
const int UPS = 120;

void GameProcess::SetCurrentScene(Scene* scene) 
{
    pause = false;
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
            if(!pause)
            currentScene->physTick(currPhys-lastPhys);
            lastPhys = currPhys;
        }

        double currDraw = glfwGetTime();
        if(currDraw-lastDraw>1.0f/maxFps){
        glClearColor(0.81,0.81,0.85,1.0);
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
        if(belarus){
            runProtocolBelarus();
            belarus = false;
        }
    }
}

void GameProcess::SetPause(bool val) 
{
    pause = val;
}

void GameProcess::runProtocolBelarus() 
{
    auto curr = new BelarusScene(this);
    curr->initResources();
    auto temp = curr->getResources();
    for(auto& el:temp.getRes())
    {
        el->subResources_.load();
        el->load();
    }
    ChangeScene(curr);
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

void GameProcess::mouse_button_callback(double xpos, double ypos, int mb, int action) 
{
    if(currentScene)
        currentScene->mouseDown(xpos,ypos,mb, action);
}

void GameProcess::char_input_callback(GLFWwindow* window, unsigned int codepoint) 
{
    if(currentScene)
        currentScene->charInput(codepoint);
}

GameProcess::GameProcess(GLFWwindow* wnd) 
: window(wnd)
{
    pause = false;
}
