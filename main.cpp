#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "game/gameprocess.hpp"
#include "baseTypes/gui/gui.hpp"  
#include "SFML/Audio.hpp"
#include <string>
#include <random>
#include <thread>

using namespace std::chrono_literals;

static GameProcess game;

static sf::Music menu_music;
static int v = 50;

static const unsigned int SCR_WIDTH = 1000;
static const unsigned int SCR_HEIGHT = 400;
static const bool def_fullScreen = false;

static bool forceChangeSong = false;
static unsigned b_counter = 0;
static bool anthemPlaying = false;
static unsigned int lastSongIndex = 0;

struct{
    bool fullscreen = def_fullScreen;
    int window_w = SCR_WIDTH;
    int window_h = SCR_HEIGHT;
}commandLineSettings;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(key==GLFW_KEY_N && action==GLFW_RELEASE)
        forceChangeSong = true;
    if(key==GLFW_KEY_B && action==GLFW_RELEASE)
        b_counter++;
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

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    v+=yoffset*5;
    if(v<0)
        v = 0;
    else if (v>100)
        v = 100;
	menu_music.setVolume(v);
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
    glfwSetScrollCallback(window, scroll_callback);
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

    std::vector<std::string> paths = {
        "data\\sound\\Kevin MacLeod _ Take the Lead.ogg",
        "data\\sound\\Kevin_MacLeod_-_06_-_Hustle.ogg",
        "data\\sound\\Kevin_MacLeod_-_Crossing_the_Divide.ogg",
        "data\\sound\\Kevin_MacLeod_-_Faster_Does_It.ogg",
        "data\\sound\\Kevin_MacLeod_-_Monkeys_Spinning_Monkeys.ogg",
        "data\\sound\\Kevin_MacLeod_-_Off_to_Osaka.ogg",
    };

    menu_music.setVolume(v);
    auto yeah = [&](){
        srand(time(0));
        while(true)
        {
            if(forceChangeSong || menu_music.getStatus()!=sf::Music::Playing)
            {
                auto curr = rand()%paths.size();
                while(curr==lastSongIndex)
                    curr = rand()%paths.size();
                menu_music.openFromFile(paths[curr]);
                menu_music.play();
                forceChangeSong = false;
                lastSongIndex = curr;
            }
            if(b_counter>5)
            {
                menu_music.openFromFile("data\\sound\\pogonya.ogg");
                menu_music.play();
                forceChangeSong = false;
                menu_music.setLoop(true);
                game.belarus = true;
                break;
            }
            b_counter = 0;
            std::this_thread::sleep_for(1s);
        }
    };

    std::thread music_thread{yeah};

    game = GameProcess(window);
    game.Init();
    game.Start();
    
    music_thread.detach();

    glfwTerminate();
    return 0;
}