#pragma once

#include <vector>
#include <fstream>

struct data_line{
    bool valid_info = false;
    float min;
    float avg;
    float max;
};

class dataHandler{
public:
    dataHandler();
    void save();
    void load();
    void clear();
    void clearLine(unsigned index);
    void update(unsigned index, float time);
private:
    std::vector<data_line> data;
};