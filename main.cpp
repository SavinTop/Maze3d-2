#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "game/gameprocess.hpp"
#include "baseTypes/gui/gui.hpp"

const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;
const bool fullScreen = false;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;

    if(fullScreen)
    {
        int x,y,w,h;
        glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &x, &y, &w, &h);
        window = glfwCreateWindow(w, h, "My Title", glfwGetPrimaryMonitor(), NULL);
    }else{
        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Maze3d", NULL, NULL);
    }


    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    gui_init();

    GameProcess game{window};
    game.Start();
    
    glfwTerminate();
    return 0;
}