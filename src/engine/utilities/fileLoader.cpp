#include "fileLoader.hpp"

namespace FileLoad
{
    std::string loadTextFile(const std::string& path, bool &succ)
    {
        std::streampos size;
        std::string out;

        std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
        if (file.is_open())
        {
            size = file.tellg();
            out.resize(size);
            file.seekg(0, std::ios::beg);
            file.read((char *)out.data(), size);
            file.close();
            succ = true;
            return out;
        }
        
        succ = false;
        return out;
    }
    
    std::vector<unsigned char> loadBinaryFile(const std::string& path, bool &succ) 
    {
        std::streampos size;
        std::vector<unsigned char> out;

        std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
        if (file.is_open())
        {
            size = file.tellg();
            out.resize(size);
            file.seekg(0, std::ios::beg);
            file.read((char *)out.data(), size);
            file.close();
            succ = true;
            return out;
        }
        
        succ = false;
        return out;
    }

    //void freeMem(char *file)
    //{
    //    if (file)
    //        delete[] file;
    //}

}; // namespace fileLoad