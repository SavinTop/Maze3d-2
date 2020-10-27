#pragma once

#include <fstream>

namespace FileLoad{
    std::string loadFile(const std::string& path, bool &succ);
};