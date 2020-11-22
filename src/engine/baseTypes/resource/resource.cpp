#include "resource.hpp"

ResourcePack::ResourcePack(){};

ResourcePack::ResourcePack(const std::vector<Resource*> resources) 
{
    setResources(resources);
}

void ResourcePack::setResources(const std::vector<Resource*>& resources)
{
    this->resources_ = resources;
}

void ResourcePack::load() {
    bool allGood = true;
    for(auto res:this->resources_){
        res->load();
        if(!res->isLoaded()){
            allGood = false;
            break;
        }
    }
    loaded = allGood;
};

void ResourcePack::unload() {
    for(auto res:this->resources_){
        res->unload();
    }
    loaded = false;
};

bool ResourcePack::isLoaded() 
{
    return loaded;
}

unsigned ResourcePack::count() 
{
    return this->resources_.size();
}

std::vector<Resource*>& ResourcePack::getRes() 
{
    return this->resources_;
}

ResourcePack getResourcesRecursively(Resource* res) 
{
    ResourcePack temp;
    for(auto& el:res->subResources_.getRes()){
        auto temp_ = getResourcesRecursively(el);
        temp.getRes().reserve(temp_.getRes().size()+temp.getRes().size());
        temp.getRes().insert(temp.getRes().end(), temp_.getRes().begin(), temp_.getRes().end());
    }
    temp.getRes().push_back(res);
    return temp;
}