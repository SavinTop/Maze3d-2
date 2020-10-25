#include "TextFile.hpp"


TextFile_res::TextFile_res(const std::string& path):Resource(path)
{
    rs = ResourceSource::EXTERNAL;
    this->path = path;
}

void TextFile_res::load() 
{
    bool succ = false;
    this->textBuffer = FileLoad::loadFile(this->path.c_str(), succ);
    this->loaded = succ;
}

void TextFile_res::unload() 
{   
    if(this->textBuffer)
        FileLoad::freeMem(this->textBuffer);
    this->loaded = false;
    this->textBuffer = nullptr;
}

char* TextFile_res::data() 
{
    return this->textBuffer;
}
