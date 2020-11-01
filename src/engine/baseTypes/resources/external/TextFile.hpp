#pragma once

#include <string>
#include "baseTypes/resource/resource.hpp"
#include "utilities/fileLoader.hpp"

namespace res::ex{
    
class TextFile : public Resource{
    public:
    TextFile(const std::string& path);
    TextFile();

    void load() override;
    void unload() override;
    void setParams(const std::string& path);

    std::string& data();

    private:
        std::string text;
};

}

