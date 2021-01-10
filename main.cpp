#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "game/gameprocess.hpp"
#include "baseTypes/gui/gui.hpp"  
#include "SFML/Audio.hpp"

static GameProcess game;

static const unsigned int SCR_WIDTH = 1000;
static const unsigned int SCR_HEIGHT = 400;
static const bool def_fullScreen = false;

struct{
    bool fullscreen = def_fullScreen;
    int window_w = SCR_WIDTH;
    int window_h = SCR_HEIGHT;
}commandLineSettings;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
}

static void character_callback(GLFWwindow* window, unsigned int codepoint)
{
	game.char_input_callback(window, codepoint);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double x,y;
    glfwGetCursorPos(window,&x,&y);
    game.mouse_button_callback(x,y,button, action);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	game.cursor_position_callback(xpos,ypos);
}

int main(int argc, char **argv)
{
    for(int i=1;i<argc;i++)
    {
        if(!strcmp(argv[i],"-fullscreen"))
            commandLineSettings.fullscreen = true;
        else if(!strcmp(argv[i],"-windowed"))
            commandLineSettings.fullscreen = false;
        else if(!strcmp(argv[i],"-window_w") && i<argc-1)
            {
                int val = atoi(argv[++i]);
                commandLineSettings.window_w = val;
                
            }
        else if(!strcmp(argv[i],"-window_h") && i<argc-1)
            {
                int val = atoi(argv[++i]);
                commandLineSettings.window_h = val;
            }
    }

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS,16);

    GLFWwindow* window;

    if(commandLineSettings.fullscreen)
    {
        int x,y,w,h;
        glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &x, &y, &w, &h);
        window = glfwCreateWindow(w, h, "My Title", glfwGetPrimaryMonitor(), NULL);
    }else{
        window = glfwCreateWindow(commandLineSettings.window_w, commandLineSettings.window_h, "Maze3d", NULL, NULL);
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
    glfwSetMouseButtonCallback(window, mouse_button_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCharCallback(window, character_callback);
    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    init_justRect();

    int window_w, window_h;
    glfwGetWindowSize(window, &window_w, &window_h);
    guiText_init(0,glm::min(window_h,window_w)*0.2,"data\\fonts\\steelfis.ttf");
    guiText_loadRangeOfCharacters(0,200);

    sf::Music menu_music;
    menu_music.openFromFile("data\\sound\\Kevin MacLeod _ Take the Lead.ogg");
    //menu_music.setLoop(true);
    menu_music.setVolume(30);
    menu_music.play();

    game = GameProcess(window);
    game.Init();
    game.Start();
    
    glfwTerminate();
    return 0;
}