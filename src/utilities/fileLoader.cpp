#include "fileLoader.hpp"

namespace FileLoad
{
    char *loadFile(const char* path, bool& succ)
    {
        std::streampos size;
        char *memblock;

        std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
        if (file.is_open())
        {
            size = file.tellg();
            memblock = new char[size+1];
            file.seekg(0, std::ios::beg);
            file.read(memblock, size);
            file.close();
            memblock[size] = 0;
            succ = true;
            return memblock;
        }
        
        succ = false;
        return 0;
    }
    void freeMem(char *file)
    {
        if (file)
            delete[] file;
    }

}; // namespace fileLoad