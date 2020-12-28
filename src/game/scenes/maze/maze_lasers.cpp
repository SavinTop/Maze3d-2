#include "maze.hpp"

void mazeScene::drawLasers(glm::mat4& proj, glm::mat4& view) 
{
    laserShader->bind();
    unsigned viewId = laserShader->getUniformLocation("view");
    unsigned projectionId = laserShader->getUniformLocation("projection");
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(proj));

    glUniform4fv(laserShader->getUniformLocation("color"), 1, glm::value_ptr(Color::getOglColor(Color::rgba(0,0,0,255))));
    
    for(int i=0;i<10;i++)
        if(!lasers[i].destroyed)
            lasers[i].holder.draw(laserShader->getProgram());
}

void mazeScene::laserPhys(float delta) 
{
    float collBox = 0.05;

    auto getPointCollBox = [&collBox](glm::vec3 pos) {
        return glm::vec4{pos.x - collBox, pos.z - collBox, pos.x + collBox, pos.z + collBox};
    };

    for(int i=0;i<10;i++)
        if(!lasers[i].destroyed)
        {
            auto& curr = lasers[i];
            curr.holder.addPosition(curr.dir*delta);
            if(glm::length(curr.holder.getPosition()-curr.start)>100)
                curr.destroyed = true;
            
            glm::ivec2 sector(curr.holder.getPosition().x / 8.0f, curr.holder.getPosition().z / 8.0f);
            auto t = checkCollision(omm, sector, getPointCollBox(curr.holder.getPosition()));
            if(t && curr.holder.getPosition().y>-3 && curr.holder.getPosition().y<3)
            {
                curr.destroyed = true;
                t->model = nullptr;
                t->fw = t->sw = glm::vec4();
            }
                
        }
            
}

void mazeScene::shotLaser(glm::vec3 start, glm::vec3 dir, float speed) 
{
    for(int i=0;i<10;i++)
        if(lasers[i].destroyed)
        {
            lasers[i].holder.setPosition(start);
            lasers[i].dir = dir*speed;
            lasers[i].destroyed = false;
            lasers[i].start = start;
            temp_i = 1;
            break;
        }
            
}