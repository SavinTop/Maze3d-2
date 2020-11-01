#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "baseTypes/scene.hpp"
#include "testScene.hpp"
#include "baseTypes/resource/resourceManager.hpp"

class GameProcess{
    public:
    GameProcess(GLFWwindow* wnd);
    void SetCurrentScene(Scene* scene);
    void Init();
    void Start();

    ResourceManager* rm;

    private:
        Scene* currentScene;
        GLFWwindow* window;
        
};