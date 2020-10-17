#include "disk_file_text_res.hpp"


disk_file_text_res::disk_file_text_res(const std::string& path, const std::string& resName):Resource(resName) 
{
    this->path = path;
}

void disk_file_text_res::load() 
{
    bool succ = false;
    this->textBuffer = FileLoad::loadFile(this->path.c_str(), succ);
    this->loaded = succ;
}

void disk_file_text_res::free() 
{   
    if(this->textBuffer)
        FileLoad::freeMem(this->textBuffer);
    this->loaded = false;
}

char* disk_file_text_res::data() 
{
    return this->textBuffer;
}
