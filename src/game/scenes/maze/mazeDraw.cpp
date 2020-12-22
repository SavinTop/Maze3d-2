#include "maze.hpp"

void mazeScene::onDraw(float delta)
{
    program->bind();
    unsigned viewId = program->getUniformLocation("view");
    unsigned projectionId = program->getUniformLocation("projection");
    unsigned lightDirId = program->getUniformLocation("lightDir");
    unsigned lightspacematrixid = program->getUniformLocation("lightSpaceMatrix");
    unsigned shadowMapid = program->getUniformLocation("shadowMap");
    glm::mat4 view = glm::mat4(1.0f);
    view = player.getCamera().getViewMatrix();
    glm::mat4 projection(1);
    projection = glm::perspective(glm::radians(fov), (float)window_w / window_h, 0.1f, 600.0f);
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));

    auto playerPos = player.getCamera().getPos() / 8.0f;
    CheckGLError();

    glm::vec3 lightDir = glm::normalize(lightPosition*(float)(maze_size_ / 5) - floor.getPosition());
    glUniform3fv(lightDirId, 1, glm::value_ptr(lightDir));

    glUniform3fv(program->getUniformLocation("viewPos"), 1, glm::value_ptr(player.getCamera().getPos()));

    glUniform1i(shadowMapid, 5);
    glActiveTexture(GL_TEXTURE0 + 5);
    auto& sett = cheatCode_h.getSettings();
    if(sett.shadows || sett.epilepsyShadows && sett.ep_shadow_state%2)
    {
        glUniform1i(program->getUniformLocation("showShadows"), 1);
        glBindTexture(GL_TEXTURE_2D, shadow_h.depthMapTex_);
        glUniformMatrix4fv(lightspacematrixid, 1, false, glm::value_ptr(lightSpaceMatrix));
    }else{
        glUniform1i(program->getUniformLocation("showShadows"), 0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    sett.ep_shadow_state++;

    glUniform1i(program->getUniformLocation("showLight"), sett.light);

    glm::vec2 real_pp{player.getCamera().getPos().x, player.getCamera().getPos().z};
    float angle = glm::radians(player.getCamera().Yaw);

    if(sett.walls){
    rth.recalculate(glm::radians(fov), real_pp, angle);

    for (auto &el : rth.getCollidedSectors())
    {
        const int sector_size_plus = 2;
        const int sector_size_minus = 2;
        glm::ivec2 sector{el.first, el.second};
        for (int i = sector.y - sector_size_minus; i <= sector.y + sector_size_plus; i++)
            for (int j = sector.x - sector_size_minus; j <= sector.x + sector_size_plus; j++)
                if (auto t = omm.get(j, i))
                {
                    t->model.draw(program->getProgram());
                }
    }
    }

    if(sett.floor)
        floor.draw(program->getProgram());

    drawLasers(projection, view);

    if(sett.skybox){
    glDepthFunc(GL_LEQUAL);
    skyboxProgram->bind();
    glUniform1i(skyboxProgram->getUniformLocation("skybox"), 0);
    viewId = skyboxProgram->getUniformLocation("view");
    projectionId = skyboxProgram->getUniformLocation("projection");
    view = glm::mat4(glm::mat3(player.getCamera().getViewMatrix()));
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));
    glBindTexture(GL_TEXTURE_2D, shadow_h.depthMapTex_);
    cmo->draw(skyboxProgram->getProgram());
    glDepthFunc(GL_LESS);
    }
    menu->draw();

    depthMapProgram->bind();
    //drawBasicTexturedRect(glm::vec4(0.0,0.0,1.0,1.0*(float)window_w/window_h), shadow_h.depthMapTex_, depthMapProgram->getProgram());
    //drawBasicTexturedRect(glm::vec4(0,0,1.0,1.0), maze_texture->getId(), depthMapProgram->getProgram());

    CheckGLError();
}
