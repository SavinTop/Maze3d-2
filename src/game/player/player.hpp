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
    bool getFixedZ(){return fixedZ;}
private:
    Camera cam;
    bool fixedZ;
};