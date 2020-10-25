#pragma once

#include <vector>
#include <string>
#include "resourceManager.hpp"

class Resource;

class ResourcePack{
    public:
        ResourcePack();
        ResourcePack(const std::vector<Resource*> resources);
        void setResources(const std::vector<Resource*>& resources);
        void load();
        void unload();
        bool isLoaded();
        unsigned count();
        std::vector<Resource*>& getRes();
    private:
        bool loaded = false;
        std::vector<Resource*> resources_;
};

class Resource{
    public:
    ResourcePack subResources_;
    std::string resName_;
    Resource(const std::string& name, ResourceManager* rm = nullptr){this->resName_ = name; this->rm = rm;}
    virtual void load() = 0;
    virtual void unload() = 0;
    bool isLoaded(){return loaded;}

    protected:
        bool loaded = false;
        ResourceSource rs;
        ResourceManager* rm;
};
