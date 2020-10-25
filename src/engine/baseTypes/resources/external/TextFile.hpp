#pragma once

#include <string>
#include "baseTypes/resource.hpp"
#include "utilities/fileLoader.hpp"

class TextFile_res : public Resource{
    public:
    TextFile_res(const std::string& path);
    void load() override;
    void unload() override;

    char* data();

    private:
        std::string path;
        char* textBuffer;
};