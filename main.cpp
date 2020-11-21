#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "game/gameprocess.hpp"
#include "baseTypes/gui/gui.hpp"  

static GameProcess game;

static const unsigned int SCR_WIDTH = 800;
static const unsigned int SCR_HEIGHT = 600;
static const bool fullScreen = true;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
}

static void character_callback(GLFWwindow* window, unsigned int codepoint)
{
	
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	game.cursor_position_callback(xpos,ypos);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS,32);

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

    glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCharCallback(window, character_callback);
    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    init_justRect();

    game = GameProcess(window);
    game.Init();
    game.Start();
    
    glfwTerminate();
    return 0;
}