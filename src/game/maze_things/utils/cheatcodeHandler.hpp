#pragma once 

#include <string>
#include <vector>
#include <map>

struct settings{
    bool shadows = true;
    bool epilepsyShadows = false;
    int ep_shadow_state = 0;
    bool skybox = true;
    bool noclip = false;
    bool floor = true;
    bool walls = true;
    bool light = true;
    bool doom = false;
    bool wireframe = false;
    bool flash = false;
};

class CheatCodeHandler{
public:
    void charInput(char c);
    void cheatCodeEntered();
    settings& getSettings(){return sett;}
    std::string& getCurrent(){return current;}
private:
    std::string current;

    settings sett;
    std::vector<std::string> cheatCodes = {
        "shadows",
        "epshadows",
        "skybox",
        "noclip",
        "restore",
        "floor",
        "light",
        "walls",
        "potato",
        "doom",
        "wireframe",
        "flash"
    };
    unsigned int matchCount();
};