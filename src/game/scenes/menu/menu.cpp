#include "menu.hpp"

void Menu::start() 
{
    guiText_init(0,glm::min(window_h,window_w)*0.2,"data\\fonts\\steelfis.ttf");
    guiText_loadRangeOfCharacters(0,129);
    menu->start();
    menu->setExitButtonClickCallBack(std::bind(&Menu::exitClicked, this));
}

void Menu::update(float delta) 
{
    int state = glfwGetKey(proc->getWnd(), GLFW_KEY_ESCAPE);
    if(state == GLFW_PRESS)
        glfwSetWindowShouldClose(proc->getWnd(), true);

    double x,y;

    glfwGetCursorPos(proc->getWnd(),&x,&y);
    bool lm = glfwGetMouseButton(proc->getWnd(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    menu->mouseInput(x,y,lm);
}

std::string text = "";

void Menu::onDraw(float delta) 
{
    menu->draw();
    
    CheckGLError();
}

ResourcePack Menu::getResources() 
{
    ResourcePack temp;
    temp.setResources(menu->getResources().getRes());
    return temp;
}

void Menu::initResources() 
{
    menu = rm->createResource<>(MenuGui(window_w, window_h, rm),sceneName);
    //testPlane = rm->createResource<>(res::ogl::Plane(glm::vec3(200,200,0), glm::vec2(200,200), {test.get()}),sceneName);
}

void Menu::exitClicked() 
{
    //glfwSetWindowShouldClose(proc->getWnd(), true);
    auto temp = new mazeScene(proc);
    temp->initResources();
    auto tempVec = temp->getResources();
    for(auto& el:tempVec.getRes())
    {
        el->subResources_.load();
        el->load();
    }
    proc->SetCurrentScene(temp);
}


Menu::Menu(GameProcess* proc)
    :Scene(proc)
{
    rm = proc->rm;
    sceneName = "menu_scene";
    glfwGetWindowSize(proc->getWnd(), &window_w, &window_h);
}
