#include "menuGui.hpp"

void MenuGui::InitializeSubResources(std::string groupName) 
{
    using namespace res::ogl;
    this->exit_idle = rm->createResource(Texture(spriteDirectory+"buttons\\exit_idle.png"),groupName);
    this->exit_active = rm->createResource(Texture(spriteDirectory+"buttons\\exit_active.png"),groupName);
    this->endless_idle = rm->createResource(Texture(spriteDirectory+"buttons\\endless_idle.png"),groupName);
    this->endless_active = rm->createResource(Texture(spriteDirectory+"buttons\\endless_active.png"),groupName);
    this->timed_idle = rm->createResource(Texture(spriteDirectory+"buttons\\timed_idle.png"),groupName);
    this->timed_active = rm->createResource(Texture(spriteDirectory+"buttons\\timed_active.png"),groupName);
    this->back_idle = rm->createResource(Texture(spriteDirectory+"buttons\\back_idle.png"),groupName);
    this->back_active = rm->createResource(Texture(spriteDirectory+"buttons\\back_active.png"),groupName);
    this->start_idle = rm->createResource(Texture(spriteDirectory+"buttons\\start_idle.png"),groupName);
    this->start_active = rm->createResource(Texture(spriteDirectory+"buttons\\start_active.png"),groupName);
    this->maze3d_idle = rm->createResource(Texture(spriteDirectory+"buttons\\maze3d_idle.png"),groupName);
    this->maze3d_active = rm->createResource(Texture(spriteDirectory+"buttons\\maze3d_active.png"),groupName);

    this->leftArrow_idle = rm->createResource(Texture(spriteDirectory+"buttons\\leftArrow_idle.png"),groupName);
    this->leftArrow_active = rm->createResource(Texture(spriteDirectory+"buttons\\leftArrow_active.png"),groupName);
    this->rightArrow_idle = rm->createResource(Texture(spriteDirectory+"buttons\\rightArrow_idle.png"),groupName);
    this->rightArrow_active = rm->createResource(Texture(spriteDirectory+"buttons\\rightArrow_active.png"),groupName);

    this->guiShader = rm->createResource(ShaderProgram("data\\shaders\\basicGui\\basic.vert","data\\shaders\\basicGui\\basic.frag", "guiProgram"),groupName);

    this->help_idle = rm->createResource(Texture(spriteDirectory+"buttons\\help_idle.png"),groupName);
    this->help_active = rm->createResource(Texture(spriteDirectory+"buttons\\help_active.png"),groupName);

    this->game_logo = rm->createResource(Texture(spriteDirectory+"maze3d logo.png"), groupName);

    this->subResources_.setResources({exit_active.get(), exit_idle.get(),
    endless_active.get(), endless_idle.get(),
    timed_active.get(), timed_idle.get(),
    back_active.get(), back_idle.get(),start_active.get(), start_idle.get(),
    leftArrow_active.get(), leftArrow_idle.get(),
    rightArrow_active.get(), rightArrow_idle.get(),
    guiShader.get(), help_active.get(), help_idle.get(), game_logo.get(), maze3d_idle.get(), maze3d_active.get()});
}