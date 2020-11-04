#pragma once

#include <vector>
#include <memory>
#include <map>
#include <stack>
#include <string>
#include "resource.hpp"

enum class LifeTime
{
    Permanent,
    Scene,
    Count
};

using resource_shared = std::shared_ptr<Resource *>;

class ResourceManager
{
public:
    bool has(const std::string &key);

    template <class T>
    T *createResource(const T &object, LifeTime lt = LifeTime::Scene)
    {
        T *out;

        std::string name = ((Resource)object).resName_;

        if (name.empty())
        {
            out = new T();
        }
        else
        {
            auto it = resources.find(name);
            if (it != resources.end())
                return (T *)(*it).second;

            out = new T();
            resources[name] = (Resource *)out;
            if (lt == LifeTime::Scene)
                tempResources.push(name);
        }
        (*out) = object;
        ((Resource *)out)->rm = this;
        ((Resource *)out)->lt = lt;
        ((Resource *)out)->InitializeSubResources();
        return out;
    }

    void deleteResource(Resource *ptr);

private:
    std::map<std::string, Resource *> resources;
    std::stack<std::string> tempResources;
};
