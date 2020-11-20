#include "player.hpp"


void Player::moveStraight(float coof) 
{
    cam.moveStraight(coof);
    if(fixedZ)
        cam.setPos(cam.getPos()*glm::vec3(1,0,1));
}

void Player::moveSideways(float coof) 
{
    cam.moveSideways(coof);
}

void Player::mouseOffsetInput(float yaw, float pitch, bool constrainPitch) 
{
    cam.addRotation(yaw, pitch, constrainPitch);
}

Camera& Player::getCamera() 
{
    return cam;
}

void Player::setFixedZ(bool val) 
{
    fixedZ = val;
}

void Player::setPosition(glm::vec3 pos) 
{
    cam.setPos(pos);
}

Player::Player(glm::vec3 position) 
{
    fixedZ = false;
    cam.setPos(position);
}
