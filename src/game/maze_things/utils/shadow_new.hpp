#pragma once

#include "glm/glm.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "game/maze_things/legacy/ObjectMazeBuilder.hpp"
#include "baseTypes/oglWrappers/shader.hpp"
#include "utilities/debug.hpp"
#include <stack>
#include <utility>

struct sh_block{
float lastUpdate;
unsigned int depthMapFBO;
unsigned int depthMapTex;
glm::mat4 lightSpaceMatrix;
glm::vec3 center;
float res;
bool loaded;
};

class Shadow_New{
public:
    void gl_init(ObjectMazeMap* omm,oglw::Shader* shadowProgram, 
    float res, glm::vec3 lightPosition, int s_w, int s_h);
    sh_block& getBlock(int x, int y);
    void update();
    void clearAll();
    void forceUpdate(int x, int y);
private:
    std::vector<std::vector<sh_block>> field;
    std::stack<std::pair<int,int>> update_stack;
    glm::vec3 lightPosition;
    ObjectMazeMap* omm;
    int s_w, s_h;
    oglw::Shader* shadowProgram;
    float res;

    void initializeBlock(int x, int y);
    void redrawBlock(int x, int y);
    void clearBlock(int x, int y);

    float lastUpdated;
};