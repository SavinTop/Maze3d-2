#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "baseTypes/scene.hpp"
#include "testScene.hpp"

class GameProcess{
    public:
    GameProcess(GLFWwindow* wnd);
    void SetCurrentScene(Scene* scene);
    void Init();
    void Start();

    private:
        Scene* currentScene;
        GLFWwindow* window;
};