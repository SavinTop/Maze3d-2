#include "resourceManager.hpp"

#include "baseTypes/scene.hpp"

void ResourceManager::clearGroup(std::string name) 
{
    if(!groups.empty())
        groups.erase(name);
}

void ResourceManager::__resourceDeleter(Resource* p) 
{
    std::string name = p->resName_;
    
    if(p->isLoaded())
        p->unload();
    delete p;

     if(!name.empty())
     {
         resources.erase(name);
         //std::cout<<name<<" deleted\n";
     }
     else
     {
         //std::cout<<"NONAME"<<" deleted\n";
     }
}
