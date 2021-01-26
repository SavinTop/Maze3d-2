#include "maze.hpp"

void mazeScene::onDraw(float delta)
{
    auto &sett = cheatCode_h.getSettings();
    glPolygonMode(GL_FRONT_AND_BACK, sett.wireframe ? GL_LINE : GL_FILL);
    program->bind();
    unsigned viewId = program->getUniformLocation("view");
    unsigned projectionId = program->getUniformLocation("projection");
    unsigned lightDirId = program->getUniformLocation("lightDir");
    unsigned lightspacematrixid = program->getUniformLocation("lightSpaceMatrix");
    unsigned shadowMapid = program->getUniformLocation("shadowMap");
    glm::mat4 view = glm::mat4(1.0f);
    view = player.getCamera().getViewMatrix();
    glm::mat4 projection(1);
    projection = glm::perspective(glm::radians(fov), (float)window_w / window_h, 0.1f, 3000.0f);
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));

    auto playerPos = player.getCamera().getPos() / 8.0f;
    CheckGLError();

    glm::vec3 lightDir = glm::normalize(lightPosition * (float)(maze_size_ / 5) - floor.getPosition());
    glUniform3fv(lightDirId, 1, glm::value_ptr(lightDir));

    glUniform3fv(program->getUniformLocation("viewPos"), 1, glm::value_ptr(player.getCamera().getPos()));

    glUniform1i(program->getUniformLocation("showLight"), sett.light);

    glm::vec2 real_pp{player.getCamera().getPos().x, player.getCamera().getPos().z};
    float angle = glm::radians(player.getCamera().Yaw);

    if (sett.walls)
    {
        rth.recalculate(glm::radians(fov), real_pp, angle);

        int wallsDrawnCounter = 0;
        for (auto &el : rth.getCollidedSectors())
        {
            const int sector_size_plus = 1;
            const int sector_size_minus = 1;
            glm::ivec2 sector{el.first, el.second};
            for (int i = sector.y - sector_size_minus; i <= sector.y + sector_size_plus; i++)
                for (int j = sector.x - sector_size_minus; j <= sector.x + sector_size_plus; j++)
                    if (auto t = omm.get(j, i))
                    {
                        glm::vec3 lightDir = glm::normalize(lightPosition);
                        glUniform3fv(lightDirId, 1, glm::value_ptr(lightDir));
                    
                        auto& curr = shds.getBlock(j,i);
                        if(proc->GetPause())
                            shds.update();
                        if(curr.loaded && (sett.shadows || sett.epilepsyShadows && sett.ep_shadow_state % 2))
                        {
                        glUniform1i(shadowMapid, 5);
                        glActiveTexture(GL_TEXTURE0 + 5);
                        glUniform1i(program->getUniformLocation("showShadows"), 1);
                        glBindTexture(GL_TEXTURE_2D, curr.depthMapTex);
                        glUniformMatrix4fv(lightspacematrixid, 1, false, glm::value_ptr(curr.lightSpaceMatrix));
                        }else
                        {
                        glUniform1i(program->getUniformLocation("showShadows"), 0);
                        glBindTexture(GL_TEXTURE_2D, 0);
                        }
                        
                        t->model.draw(program->getProgram());
                        if (t->child.get())
                            t->child->draw(program->getProgram());
                        wallsDrawnCounter++;
                        if (sett.floor && j!=omm.width()-1 && i!=omm.height()-1)
                        {
                            floor.setPosition(glm::vec3(j*8+4, -3, i*8+4));
                            floor.draw(program->getProgram());
                        }
                            
                    }
        }
        //system("cls");
        //std::cout<<wallsDrawnCounter<<' '<<rth.getCollidedSectors().size()<<std::endl;
    }

    drawLasers(projection, view);
    sett.ep_shadow_state++;

    if (sett.skybox)
    {
        glDepthFunc(GL_LEQUAL);
        skyboxProgram->bind();
        glUniform1i(skyboxProgram->getUniformLocation("skybox"), 0);
        viewId = skyboxProgram->getUniformLocation("view");
        projectionId = skyboxProgram->getUniformLocation("projection");
        auto view_sky = glm::mat4(glm::mat3(player.getCamera().getViewMatrix()));
        glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view_sky));
        glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));
        cmo->draw(skyboxProgram->getProgram());
        glDepthFunc(GL_LESS);
    }

    if (!timed_ended)
    {
        epm_program->bind();
        glUniform4fv(epm_program->getUniformLocation("color"), 1, glm::value_ptr(Color::getOglColor(Color::rgba(255, 255, 0, 125))));
        viewId = epm_program->getUniformLocation("view");
        projectionId = epm_program->getUniformLocation("projection");
        glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));
        epm.draw(epm_program->getProgram());
    }

    menu->draw();

    if (sett.doom)
    {
        pistolProgram->bind();
        if (window_w > window_h)
            drawBasicTexturedRect(glm::vec4(0, 0, 1.0 * (float)window_w / window_h, 2.0), pistol_pack->getId((int)temp_i % 6), pistolProgram->getProgram());
        else
            drawBasicTexturedRect(glm::vec4(0, 0, 1.0 * (float)window_h / window_w, 2.0), pistol_pack->getId((int)temp_i % 6), pistolProgram->getProgram());
        if ((int)temp_i % 6 != 0)
            temp_i += delta * 30;

        //drawBasicTexturedRect(glm::vec4(0,0,1.0,1.0), shds.getBlock(3,0).depthMapTex, pistolProgram->getProgram());
    }

    CheckGLError();
    //drawBasicTexturedRect(glm::vec4(0.0,0.0,1.0,1.0*(float)window_w/window_h), shds.getBlock(1,1).depthMapTex, pistolProgram->getProgram());

    CheckGLError();
    frameCounter++;
}
