#include "maze.hpp"

void mazeScene::physTick(float delta)
{
    auto& sett = cheatCode_h.getSettings();
    const float collBox = 0.2;

    glm::vec3 lastPlayerPos = player.getCamera().getPos();

    float playerSpeed = 10;

    if (glfwGetKey(proc->getWnd(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        playerSpeed *= 2;
        fov = glm::min(70.0f, fov + 10 * delta);
    }
    else
        fov = glm::max(60.0f, fov - 10 * delta);

    if (glfwGetKey(proc->getWnd(), GLFW_KEY_W) == GLFW_PRESS)
        player.moveStraight(delta * playerSpeed);
    if (glfwGetKey(proc->getWnd(), GLFW_KEY_S) == GLFW_PRESS)
        player.moveStraight(-delta * playerSpeed);
    if (glfwGetKey(proc->getWnd(), GLFW_KEY_D) == GLFW_PRESS)
        player.moveSideways(delta * playerSpeed);
    if (glfwGetKey(proc->getWnd(), GLFW_KEY_A) == GLFW_PRESS)
        player.moveSideways(-delta * playerSpeed);

    player.setFixedZ(!sett.noclip);

    auto getPointCollBox = [&collBox](glm::vec3 pos) {
        return glm::vec4{pos.x - collBox, pos.z - collBox, pos.x + collBox, pos.z + collBox};
    };

    glm::vec3 playerPos = player.getCamera().getPos();
    glm::ivec2 sector(playerPos.x / 8.0f, playerPos.z / 8.0f);
    menu->debug_setDebugPlayerPos(playerPos.x, playerPos.y);
    glm::vec3 tempPos = playerPos;
    auto t = checkCollision(omm, sector, getPointCollBox(tempPos));

    if (!sett.noclip && t && playerPos.y < 4)
    {
        auto fixedX = tempPos * glm::vec3(0, 1, 1) + glm::vec3(lastPlayerPos.x, 0, 0);
        auto tx = checkCollision(omm, sector, getPointCollBox(fixedX));
        auto fixedY = tempPos * glm::vec3(1, 1, 0) + glm::vec3(0, 0, lastPlayerPos.z);
        auto ty = checkCollision(omm, sector, getPointCollBox(fixedY));
        if (!tx || ty)
        {
            tempPos.x = fixedX.x;
        }
        if (!ty || tx)
        {
            tempPos.z = fixedY.z;
        }

        player.setPosition(tempPos);
    }

    //if (coll(getPointCollBox(playerPos), omm.get(omm.width()-2, omm.height()-1)->fw))
    if (playerPos.x<0 || playerPos.x>omm.width()* 8 - 6 || playerPos.z<0 || playerPos.z>omm.height()* 8 - 6)
    {
        if(timed)
            Lvld0ne_timed();
        else
            Lvld0ne_endless();
    }

    laserPhys(delta);

    if(timed && !proc->GetPause())
    {
        float curr = glfwGetTime();
        timer+=curr-last_time;
        menu->timer_setTime(timer);
        last_time = curr;
    } 
}