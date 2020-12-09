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
    void SetPause(bool val);
    bool GetPause(){return pause;};
    GLFWwindow* getWnd();
    ResourceManager* rm;

    void cursor_position_callback(double xpos, double ypos);
    void mouse_button_callback(double xpos, double ypos, int mb, int action);

    private:

    Scene* currentScene;
    Scene* nextScene;
    GLFWwindow* window;
    bool pause;
};