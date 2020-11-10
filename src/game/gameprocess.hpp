#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "baseTypes/scene.hpp"
#include "baseTypes/resource/resourceManager.hpp"
#include <map>

class GameProcess{
    public:
    GameProcess(GLFWwindow* wnd);
    void SetCurrentScene(Scene* scene);
    void Init();
    void Start();
    GLFWwindow* getWnd();
    ResourceManager* rm;

    private:
        Scene* currentScene;
        GLFWwindow* window;
        
};