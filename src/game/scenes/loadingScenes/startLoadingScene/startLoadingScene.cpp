#include "startLoadingScene.hpp"
#include "scenes/menu/menu.hpp"

#include <thread>

using namespace std::chrono_literals;

StartLoadingScene::StartLoadingScene(GameProcess* proc):Scene(proc)
{
    nextScene = new Menu(proc);
    currentIndex = 0;
    sceneName = "start_loading_scene";
}

void StartLoadingScene::start() 
{
    nextScene->initResources();
    auto temp = nextScene->getResources().getRes();
    for(auto& el:temp){
        auto subRes = el->subResources_.getRes();
        for(auto& subel:subRes)
            resourcesToLoad.push_back(subel);
        resourcesToLoad.push_back(el);
    }
}

void StartLoadingScene::update(float delta) 
{
    if(currentIndex>=resourcesToLoad.size()){
        std::this_thread::sleep_for(1s);
        proc->SetCurrentScene(nextScene);
        return;
    }
    auto& t = resourcesToLoad[currentIndex];
    std::cout<<t->resName_<<std::endl;
    t->load();
    currentIndex++;
}

void StartLoadingScene::onDraw(float delta) 
{
    glClear(GL_COLOR_BUFFER_BIT);
    loadingShader->bind();
    unsigned viewId = loadingShader->getUniformLocation("view");
    unsigned projectionId = loadingShader->getUniformLocation("projection");
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection(1);
    //glUniform1f(loadingShader->getUniformLocation("loadingProgress"), (float)currentIndex/resourcesToLoad.size());
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));
    loadingPlane->setScale(glm::vec3((float)currentIndex/resourcesToLoad.size(), 1,1));
    loadingPlane->draw(*loadingShader);
}

ResourcePack StartLoadingScene::getResources() 
{
    return ResourcePack({loadingShader.get(), loadingPlane.get()});
}

void StartLoadingScene::initResources() 
{
    loadingShader = rm->createResource<>(
    res::ogl::ShaderProgram("data/shaders/startLoadingScreen.vert",
                            "data/shaders/startLoadingScreen.frag",
                            "basic program"),sceneName);
    loadingPlane = rm->createResource<>(
        res::ogl::Plane(glm::vec3(0, 0 , 0), glm::vec2(2, 0.5)),sceneName
    );
}
