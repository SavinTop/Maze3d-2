#include "menu.hpp"

void Menu::start() 
{
    menu->start();
    menu->setExitButtonClickCallBack(std::bind(&Menu::exitClicked, this));
    menu->setEndlessStartButtonClickCallBack(std::bind(&Menu::endless_start_clicked, this));
    menu->setTimedStartButtonClickCallBack(std::bind(&Menu::timed_start_clicked, this));
}

void Menu::update(float delta) 
{
    int state = glfwGetKey(proc->getWnd(), GLFW_KEY_ESCAPE);
    if(state == GLFW_PRESS)
        glfwSetWindowShouldClose(proc->getWnd(), true);
    
}

std::string text = "";

void Menu::onDraw(float delta) 
{
    menu->draw();
    
    CheckGLError();
}

ResourcePack Menu::getResources() 
{
    return ResourcePack({menu.get()});
}

void Menu::initResources() 
{
    menu = rm->createResource<>(MenuGui(window_w, window_h, rm, proc->getWnd()),sceneName, "mainmenugui");
    //testPlane = rm->createResource<>(res::ogl::Plane(glm::vec3(200,200,0), glm::vec2(200,200), {test.get()}),sceneName);
}

void Menu::mouseDown(double xpos, double ypos, int mb, int action) 
{
    bool lm = mb==GLFW_MOUSE_BUTTON_LEFT && action==GLFW_RELEASE;
    if(lm)
        menu->mouseInput(xpos,ypos,lm);
        menu->mouseInput(xpos,ypos,false);
}

void Menu::mouseMove(double xpos, double ypos) 
{
    menu->mouseInput(xpos,ypos,false);
}

void Menu::exitClicked() 
{
    glfwSetWindowShouldClose(proc->getWnd(), true);
}

void Menu::endless_start_clicked() 
{
    auto next = new LoadingScene(proc, new mazeScene(proc, menu->get_endless_lvl()));
    next->initResources();
    auto temp = next->getResources();
    for(auto& el:temp.getRes())
    {
        el->subResources_.load();
        el->load();
    }
    proc->ChangeScene(next);
}

void Menu::timed_start_clicked() 
{
    auto next = new LoadingScene(proc, new mazeScene(proc, menu->get_timed_lvl(), true));
    next->initResources();
    auto temp = next->getResources();
    for(auto& el:temp.getRes())
    {
        el->subResources_.load();
        el->load();
    }
    proc->ChangeScene(next);
}


Menu::Menu(GameProcess* proc)
    :Scene(proc)
{
    rm = proc->rm;
    sceneName = "menu_scene";
    glfwGetWindowSize(proc->getWnd(), &window_w, &window_h);
}
