#pragma once

#include <vector>
#include <map>
#include <string>

class Resource;

enum class ResourceSource{
    INTERNAL, EXTERNAL
};

class ResourceManager{
public:
    bool Has(Resource* res);
private:
    std::map<ResourceSource, std::map<std::string, Resource*>> resources_;
};

/*

*/