#pragma once

#include <vector>
#include <memory>
#include <map>
#include <stack>
#include <string>
#include <iostream>
#include <functional>
#include "resource.hpp"

class Scene;

class ResourceManager
{
public:
    bool has(const std::string &key);

    void __resourceDeleter(Resource* p);

    template <class T>
    std::shared_ptr<T> createResource(const T &object, std::string groupName = "general", std::string resname = "")
    {
        using namespace std::placeholders;
        std::shared_ptr<T> out;
        std::string name;
        
        name = resname.empty()?((Resource)object).resName_:resname;

        if (name.empty())
        {
            out.reset(new T(), std::bind(ResourceManager::__resourceDeleter, this, _1));
        }
        else
        {
            auto it = resources.find(name);
            if (it != resources.end())
                return std::static_pointer_cast<T>((*it).second.lock());

            out.reset(new T(), std::bind(ResourceManager::__resourceDeleter, this, _1));
            resources[name] = out;
        }
        (*out) = object;
        ((Resource *)out.get())->rm = this;
        ((Resource *)out.get())->InitializeSubResources(groupName);

        if(!groupName.empty())
            groups[groupName].push_back(std::static_pointer_cast<Resource>(out));

        return out;
    }

    void clearGroup(std::string name);

private:
    std::map<std::string, std::weak_ptr<Resource>> resources;
    std::map<std::string, std::vector<std::shared_ptr<Resource>>> groups;
};
