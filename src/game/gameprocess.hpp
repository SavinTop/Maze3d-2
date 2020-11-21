#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "baseTypes/scene.hpp"
#include "baseTypes/resource/resourceManager.hpp"
#include <map>

class GameProcess{
    public:
    GameProcess(){};
    GameProcess(GLFWwindow* wnd);
    void SetCurrentScene(Scene* scene);
    void ChangeScene(Scene* scene);
    void Init();
    void Start();
    GLFWwindow* getWnd();
    ResourceManager* rm;

    void cursor_position_callback(double xpos, double ypos);

    private:

    Scene* currentScene;
    Scene* nextScene;
    GLFWwindow* window;
        
};