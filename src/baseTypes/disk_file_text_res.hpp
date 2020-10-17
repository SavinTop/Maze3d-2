#pragma once

#include <string>
#include "baseTypes/resource.hpp"
#include "utilities/fileLoader.hpp"

class disk_file_text_res : public Resource{
    public:
    disk_file_text_res(const std::string& path, const std::string& resName);
    void load() override;
    void free() override;

    char* data();

    private:
        std::string path;
        char* textBuffer;
};