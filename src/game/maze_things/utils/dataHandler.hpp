#pragma once

#include <vector>
#include <fstream>

struct data_line{
    bool valid_info = false;
    float min;
    float max;
    float sum = 0;
    unsigned count = 0;
};

class dataHandler{
public:
    dataHandler();
    void save();
    void load();
    void clear();
    void clearLine(unsigned index);
    void update(unsigned index, float time);
    std::vector<data_line>& getData(){return data;};
private:
    std::vector<data_line> data;
};