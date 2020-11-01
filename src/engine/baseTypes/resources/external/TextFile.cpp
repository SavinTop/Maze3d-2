#include "TextFile.hpp"

namespace res::ex{

TextFile::TextFile(const std::string& path):Resource()
{
    setParams(path);
}

TextFile::TextFile() :Resource()
{
    
}

void TextFile::load() 
{
    bool succ = false;
    this->text = FileLoad::loadFile(this->resName_, succ);

    this->loaded = succ;
}

void TextFile::unload() 
{   
    this->text.clear();
    this->loaded = false;
}

void TextFile::setParams(const std::string& path) 
{
    this->resName_ = path;
}

std::string& TextFile::data() 
{
    return this->text;
}

}