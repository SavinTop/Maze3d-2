#pragma once 

#include <render/camera.hpp>

class Player{
public:
    Player(glm::vec3 position = {0.0,0.0,0.0});

    void moveStraight(float coof);
    void moveSideways(float coof);

    void mouseOffsetInput(float yaw, float pitch, bool constrainPitch = true);
    Camera& getCamera();
    void setFixedZ(bool val);
    bool getFixedZ(){return cam.fixed_z;}
    void setPosition(glm::vec3 pos);
private:
    Camera cam;
};