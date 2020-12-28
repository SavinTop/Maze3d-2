#include "dataHandler.hpp"


void dataHandler::save() 
{
    std::ofstream file;
    file.open("data\\timed.results", std::ios::binary | std::ios::out);
    for(auto& el:data)
    {
        file.write((char*)&el, sizeof(el));
    }
    file.close();
}

void dataHandler::load() 
{
    std::ifstream file;
    file.open("data\\timed.results", std::ios::binary | std::ios::in);
    for(auto& el:data)
    {
        /*
        file.read((char*)&el.valid_info, sizeof(el.valid_info));
        file.read((char*)&el.min, sizeof(el.min));
        file.read((char*)&el.avg, sizeof(el.avg));
        file.read((char*)&el.max, sizeof(el.max));
        */
        file.read((char*)&el, sizeof(el));
    }
    file.close();
}

void dataHandler::clear() 
{
    data.clear();
    data.resize(20);
}

void dataHandler::clearLine(unsigned index) 
{
    data[index] = data_line();
}

void dataHandler::update(unsigned index, float time) 
{
    
}

dataHandler::dataHandler() 
{
    data.resize(20);
}
