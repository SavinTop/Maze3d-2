#include "resourceManager.hpp"

#include "baseTypes/scene.hpp"

void ResourceManager::clearGroup(std::string name) 
{
    if(!groups.empty())
        groups.erase(name);
}

void ResourceManager::__resourceDeleter(Resource* p) 
{
    std::cout<<p->resName_<<" deleted\n";
    if(!p->resName_.empty())
        resources.erase(p->resName_);
    p->unload();
    delete p;
}
