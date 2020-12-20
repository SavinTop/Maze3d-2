#include "raycastingHandler.hpp"

RaycastingHandler::RaycastingHandler(int ray_count, ObjectMazeMap* mmp) 
{
    this->ray_count = ray_count;
    this->mmp = mmp;
    this->rays.resize(ray_count);
}

void RaycastingHandler::recalculate(float fov, glm::vec2 camPos, float camDir) 
{
    collidedSectors.clear();
    fov = glm::half_pi<float>()+0.5;
    float step = fov/ray_count;
    for(int i=0;i<ray_count;i++)
    {
        float dir = camDir+(-fov/2+step*i);
        auto& curr = rays[i];
        curr.start = camPos;
        curr.currPos = camPos;
        curr.end = camPos+glm::vec2(cos(dir)*1000,sin(dir)*1000);
        curr.step = glm::vec2(cos(dir)*8,sin(dir)*8);
        curr.collapsed = false;
    }

    bool allRaysCollapsed = false;
    int counter = 0;
    while(!allRaysCollapsed && counter<20)
    {
        counter++;
        allRaysCollapsed = true;
        for(int i=0;i<ray_count;i++)
        {
            auto& curr = rays[i];
            if(curr.collapsed) continue;
            glm::ivec2 sector{curr.currPos/8.0f};
            bool collided = false;
            const int sector_size = 1;
            for(int i=sector.y-sector_size;i<=sector.y+sector_size && !collided;i++)
                for(int j=sector.x-sector_size;j<=sector.x+sector_size && !collided;j++)
                if(auto t = mmp->get(j,i))
                {
                    auto fw = t->fw;
                    auto sw = t->sw;
                    collided = lineRect(curr.start.x, curr.start.y, curr.end.x, curr.end.y, fw.x, fw.y,abs(fw.x-fw.z),abs(fw.y-fw.w));
                    if(!collided && t->wt == wallType::Corner)
                        collided |= lineRect(curr.start.x, curr.start.y, curr.end.x, curr.end.y, sw.x, sw.y,abs(sw.x-sw.z),abs(sw.y-sw.w));
                    if(collided)
                    {
                        curr.collapsed = true;
                    }
                    collidedSectors.insert(std::make_pair<int,int>((int)sector.x, (int)sector.y));
                }
            curr.currPos+=curr.step;
            allRaysCollapsed = false;
        }
    }
}
