#pragma once

#include "baseTypes/scene.hpp"
#include "render/render.hpp"
#include "gameprocess.hpp"
#include <iostream>
#include <vector>

class TestScene : public Scene{
public:
TestScene(GameProcess* proc);
void start() override;
void update(float delta) override;
ResourcePack getResources() override;
private:
ShaderProgram program;
std::vector<float> vertices;
unsigned int VBO;
unsigned int VAO;
};

