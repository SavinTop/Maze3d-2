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

class mazeScene : public Scene{
    public:
    mazeScene(GameProcess* proc);
    void start() override;
    void update(float delta) override;
    void onDraw(float delta) override;
    void physTick(float delta) override;
    ResourcePack getResources() override;
    void initResources() override;
    void mouseMove(double xpos, double ypos) override;
    private:
    mazeObject* checkCollision(ObjectMazeMap& omm, glm::ivec2 sector, glm::vec4 playerRect);

    std::shared_ptr<res::ogl::Model> lineWallModel;
    std::shared_ptr<res::ogl::Model> rootWallModel;
    std::shared_ptr<res::ogl::Model> cornerWallModel;
    std::shared_ptr<res::ogl::ShaderProgram> program;
    std::shared_ptr<res::ogl::Texture> tempTexture;

    std::shared_ptr<res::ogl::CubemapTexture> cmt;
    std::shared_ptr<res::ogl::ShaderProgram> skyboxProgram;
    std::shared_ptr<res::ogl::CubemapModel> cmo;
    Player player;

    int window_w;
    int window_h;

    MazeMapGenerator _mapGenerator;
    MazeBuilder maze;
    ObjectMazeMap omm;
    std::shared_ptr<MazeGui> menu;

    float lastMouseInput;
};
