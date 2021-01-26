#pragma once

#include "baseTypes/resources/internal/OGL/glresources.hpp"
#include "gameprocess.hpp"
#include "baseTypes/color.hpp"
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "baseTypes/resources/internal/OGL/glresources.hpp"
#include "render/camera.hpp"
#include "maze_things/legacy/MazeMapGenerator.hpp"
#include "maze_things/legacy/ObjectMazeBuilder.hpp"
#include "baseTypes/gui/gui.hpp"
#include "player/player.hpp"
#include "mazeGui.hpp"
#include "maze_things/utils/collisionChecker.hpp"
#include "maze_things/floor/floorModel.hpp"
#include "scenes/loadingScenes/LoadingScene.hpp"
#include "maze_things/utils/raycastingHandler.hpp"
#include "maze_things/utils/shadowHandler.hpp"
#include "maze_things/utils/cheatCodeHandler.hpp"
#include "maze_things/doomsDay/laserModel.hpp"
#include "maze_things/doomsDay/laserObj.hpp"
#include "maze_things/utils/dataHandler.hpp"
#include "maze_things/utils/innerModels/endpointModel.hpp"
#include "game/maze_things/utils/shadow_new.hpp"

class mazeScene : public Scene{
    public:
    mazeScene(GameProcess* proc, int maze_size, bool timed = false);
    ~mazeScene();
    void start() override;
    void update(float delta) override;
    void onDraw(float delta) override;
    void physTick(float delta) override;
    ResourcePack getResources() override;
    void initResources() override;
    void mouseMove(double xpos, double ypos) override;
    void mouseDown(double xpos, double ypos, int mb, int action) override;
    void charInput(unsigned int character) override;
    void okClicked();
    void drawLasers(glm::mat4& proj, glm::mat4& view);
    void laserPhys(float delta);
    void shotLaser(glm::vec3 start, glm::vec3 dir, float speed);

    void Lvld0ne_endless();
    void Lvld0ne_timed();
    void goToMainMenu();

    private:
    std::shared_ptr<res::ogl::Model> lineWallModel;
    std::shared_ptr<res::ogl::Model> rootWallModel;
    std::shared_ptr<res::ogl::Model> cornerWallModel;
    std::shared_ptr<res::ogl::Model> xmasTreeModel;
    std::shared_ptr<res::ogl::Model> bugattiModel;
    FloorModel floor;
    LaserModel laserModel;
    std::shared_ptr<res::ogl::ShaderProgram> laserShader;
    std::shared_ptr<res::ogl::Texture> floorTexture;
    std::shared_ptr<res::ogl::Texture> floorTextureNormal;
    std::shared_ptr<res::ogl::ShaderProgram> program;

    std::shared_ptr<res::ogl::CubemapTexture> cmt;
    std::shared_ptr<res::ogl::ShaderProgram> skyboxProgram;
    std::shared_ptr<res::ogl::CubemapModel> cmo;
    Player player;

    int window_w;
    int window_h;

    MazeMapGenerator _mapGenerator;
    MazeBuilder maze;
    ObjectMazeMap omm;
    std::shared_ptr<res::ogl::Texture> maze_texture;
    std::shared_ptr<MazeGui> menu;
    Camera topDownView;

    float lastMouseInput;
    float fov;

    int maze_size_;

    RaycastingHandler rth;
    ShadowHandler shadow_h;

    //TODO do it fine, not like this
    std::shared_ptr<res::ogl::ShaderProgram> shadowProgram;
    std::shared_ptr<res::ogl::ShaderProgram> pistolProgram;
    glm::mat4 lightSpaceMatrix;

    glm::vec3 lightPosition = glm::vec3(-12.0f, 14.0f, -20.0f);

    CheatCodeHandler cheatCode_h;

    laserObject lasers[10] = {};

    std::shared_ptr<res::ogl::TexturePack> pistol_pack;
    float temp_i = 0;

    bool timed;
    float last_time;
    float timer; 
    unsigned frameCounter;
    unsigned tempSum;
    dataHandler dh_test;

    EndPointModel epm;
    std::shared_ptr<res::ogl::ShaderProgram> epm_program;
    bool timed_ended;

    Shadow_New shds;
};
