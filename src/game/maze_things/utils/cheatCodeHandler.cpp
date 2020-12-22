#include "cheatcodeHandler.hpp"


void CheatCodeHandler::charInput(char c) 
{
    current+=c;
    if(current.size()==2 && current[0]==c)
        current = c;
    unsigned int mc = matchCount();
    if(mc==0)
        current = "";
    else if(mc==1)
        cheatCodeEntered();
}

void CheatCodeHandler::cheatCodeEntered() 
{
    std::string temp = std::move(current);
    current = "";
    if(temp=="shadows")
    {
        sett.shadows = !sett.shadows;
        sett.epilepsyShadows = false;
    }
    else if(temp=="epshadows")
    {
        sett.shadows = false;
        sett.epilepsyShadows = !sett.epilepsyShadows;
    }else if(temp=="skybox")
    {
        sett.skybox = !sett.skybox;
    }else if(temp=="noclip")
    {
        sett.noclip = !sett.noclip;
    }else if(temp=="restore")
    {
        sett = settings();
    }else if(temp=="floor")
    {
        sett.floor = !sett.floor;
    }else if(temp=="light")
    {
        sett.light = !sett.light;
    }else if(temp=="walls")
    {
        sett.walls = !sett.walls;
    }else if(temp=="potato")
    {
        sett.light = false;
        sett.shadows = false;
        sett.epilepsyShadows = false;
        sett.skybox = false;
    }else if(temp=="doom")
    {
        sett.doom = !sett.doom;
    }
    else
        current = std::move(temp);

}

unsigned int CheatCodeHandler::matchCount() 
{
    unsigned int counter = 0;
    for(auto& el:cheatCodes)
        counter+=(el.rfind(current,0)==0);
    return counter;
}
