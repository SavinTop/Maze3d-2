#pragma once

#include <fstream>

namespace FileLoad{
    char* loadFile(const char* path, bool &succ);
    void freeMem(char* file);
};