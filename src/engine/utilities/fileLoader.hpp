#pragma once

#include <fstream>
#include <vector>

namespace FileLoad{
    std::string loadTextFile(const std::string& path, bool &succ);
    std::vector<unsigned char> loadBinaryFile(const std::string& path, bool &succ);
};