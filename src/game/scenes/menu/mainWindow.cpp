#include "menuGui.hpp"
#include <windows.h>

void MenuGui::initMain() 
{
    float topOffset = -0.33;
    float downButt = -0.95;
    float dist = 0.25;

    main = GuiWindow(w,h);
    main_fbox = FullscreenBox(nullptr, w, h);
    main_exit_button = Button(nullptr, exit_idle.get(), exit_active.get());
    main_endless_button = Button(nullptr, endless_idle.get(), endless_active.get());
    main_timed_button = Button(nullptr, timed_idle.get(), timed_active.get());
    main_help_button = Button(nullptr, help_idle.get(), help_active.get());
    main_game_logo = Button(nullptr, game_logo.get(), game_logo.get());
    main_maze3d_button = Button(nullptr, maze3d_idle.get(), maze3d_active.get());

    main_fbox.setParent(&main);
    main_exit_button.setParent(&main_fbox);
    main_endless_button.setParent(&main_fbox);
    main_timed_button.setParent(&main_fbox);
    main_help_button.setParent(&main_fbox);
    main_game_logo.setParent(&main_fbox);
    main_maze3d_button.setParent(&main_fbox);

    main_exit_button.setSize(0.3f,0.09f);
    main_exit_button.setPosition(0.0f,downButt+1*dist);

    main_endless_button.setSize(0.3f,0.09f);
    main_endless_button.setPosition(0.0f,downButt+5*dist);
    main_endless_button.setClickCallback(std::bind(&MenuGui::endlessClick, this));

    main_timed_button.setSize(0.3f,0.09f);
    main_timed_button.setPosition(0.0f,downButt+4*dist);
    main_timed_button.setClickCallback(std::bind(&MenuGui::timedClick, this));

    main_help_button.setSize(0.3f,0.09f);
    main_help_button.setPosition(0.0f,downButt+2*dist);
    main_help_button.setClickCallback(std::bind(&MenuGui::helpClick, this));

    main_maze3d_button.setSize(0.3f,0.09f);
    main_maze3d_button.setPosition(0.0f,downButt+3*dist);
    main_maze3d_button.setClickCallback(std::bind(&MenuGui::maze3d_click, this));

    main_game_logo.setSize(1.0f,0.22f);
    main_game_logo.setPosition(0.0f,topOffset+1.0f);

    auto temp = getChildrenRecurs(&main);
    main.setDrawableChildArr(temp);
}

void MenuGui::setExitButtonClickCallBack(std::function<void(void)> click) 
{
    main_exit_button.setClickCallback(click);
}

void MenuGui::maze3d_click() 
{
    ShellExecute(NULL, "open", "Maze.exe", NULL, "data\\maze_first", SW_SHOWDEFAULT);
    glfwSetWindowShouldClose(wnd, true);
}

void MenuGui::endlessClick() 
{
    currentWindow = &endless;
}

void MenuGui::timedClick() 
{
    currentWindow = &timed;
}

void MenuGui::helpClick() 
{
    ShellExecute(NULL, "open", "index.html", NULL, NULL, SW_SHOWDEFAULT);
}