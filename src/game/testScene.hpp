#pragma once

#include "baseTypes/scene.hpp"
#include "render/render.hpp"
#include <iostream>
#include <vector>

class TestScene : public Scene{
public:
TestScene(GameProcess* proc);
void Start() override;
void Update(float delta) override;
ResourcePack getResources() override;
private:
ShaderProgram program;
std::vector<float> vertices;
unsigned int VBO;
};

