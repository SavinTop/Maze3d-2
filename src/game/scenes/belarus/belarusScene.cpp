#include "belarusScene.hpp"

#include <thread>
#include "GLFW/glfw3.h"
#include "gameprocess.hpp"

using namespace std::chrono_literals;

BelarusScene::BelarusScene(GameProcess *proc) : Scene(proc)
{
    sceneName = "belarus";
    glfwGetWindowSize(proc->getWnd(), &window_w, &window_h);
}

void BelarusScene::start()
{
    
}

void BelarusScene::update(float delta)
{
    int state = glfwGetKey(proc->getWnd(), GLFW_KEY_ESCAPE);
    if(state == GLFW_PRESS)
        glfwSetWindowShouldClose(proc->getWnd(), true);
}

void BelarusScene::onDraw(float delta)
{
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    program->bind();
    unsigned viewId = program->getUniformLocation("view");
    unsigned projectionId = program->getUniformLocation("projection");
    unsigned modelId = program->getUniformLocation("model");
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection(1);
    //projection = glm::ortho(0.0f, (float)window_w, 0.0f, (float)window_h, 0.0f, 100.0f);
    glm::mat4 model;
    model = glm::mat4{1.0};
    model = glm::translate(model, glm::vec3(0.0));
    model = glm::scale(model, glm::vec3(2.0,0.66,1.0));

    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(modelId, 1, GL_FALSE, glm::value_ptr(model));

    glUniform4fv(program->getUniformLocation("color"), 1, glm::value_ptr(Color::getOglColor(Color::rgba(255,0,0,255))));
    glBindVertexArray(gui_getVAOid());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //lbl.draw(textProgram);
    CheckGLError();
}

ResourcePack BelarusScene::getResources()
{
    return ResourcePack({program.get()});
}

void BelarusScene::initResources()
{
    program = rm->createResource<>(
        res::ogl::ShaderProgram("data\\shaders\\colorOnlyGui\\basic.vert",
                                "data\\shaders\\colorOnlyGui\\basic.frag",
                                "belarus shader"), sceneName);
}
