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
    this->guiShader = rm->createResource(ShaderProgram("data\\shaders\\basicGui\\basic.vert","data\\shaders\\basicGui\\basic.frag", "guiProgram"),groupName);
}

ResourcePack& MenuGui::getResources() 
{
    r_pack = ResourcePack({exit_active.get(), exit_idle.get(),
    endless_active.get(), endless_idle.get(),
    timed_active.get(), timed_idle.get(),
    back_active.get(), back_idle.get(),
    guiShader.get()});
    return r_pack;
}