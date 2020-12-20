#include "LoadingScene.hpp"
#include "scenes/menu/menu.hpp"

#include <thread>

using namespace std::chrono_literals;

LoadingScene::LoadingScene(GameProcess *proc, Scene* nextScene) : Scene(proc)
{
    this->nextScene = nextScene;
    currentIndex = 0;
    sceneName = "start_loading_scene";
    glfwGetWindowSize(proc->getWnd(), &window_w, &window_h);
    fsb = FullscreenBox(nullptr, window_w, window_h);
    lb.setParent(&fsb);
    lb.setPosition(0.0f,0.0f);
    lb.setSize(0.5f, 0.03f);
    lb.setColor(Color::rgba(0,0,0,255));
    
    lbl.setParent(&fsb);
    lbl.setPosition(0.0f,-0.03f*2);
    lbl.setSize(0.25f, 0.02f);
    lbl.setTextAlign(textAlign::Left);
}

void LoadingScene::start()
{
    nextScene->initResources();
    auto temp = nextScene->getResources().getRes();
    for (auto &el : temp)
    {
        auto tempRes = getResourcesRecursively(el);
        resourcesToLoad.insert(resourcesToLoad.end(), tempRes.getRes().begin(), tempRes.getRes().end());
    }
}

void LoadingScene::update(float delta)
{
    if (currentIndex >= resourcesToLoad.size())
    {
        proc->ChangeScene(nextScene);
        return;
    }
    auto &t = resourcesToLoad[currentIndex];
    t->load();
    currentIndex++;
    if(!t->resName_.empty())
    lbl.setText(t->resName_);
    lb.setProgress((float)currentIndex/resourcesToLoad.size());
    unsigned char c = (unsigned char)(lb.getProgress()/2*255);
    lb.setColor(Color::rgba(c,c,c,255));
}

void LoadingScene::onDraw(float delta)
{
    glClear(GL_COLOR_BUFFER_BIT);
    loadingShader->bind();
    unsigned viewId = loadingShader->getUniformLocation("view");
    unsigned projectionId = loadingShader->getUniformLocation("projection");
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection(1);
    projection = glm::ortho(0.0f, (float)window_w, 0.0f, (float)window_h, 0.0f, 100.0f);
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));

    lb.draw(loadingShader->getProgram());

    auto textProgram = guiText_getTextShader();
    textProgram.bind();
    projectionId = textProgram.getUniformLocation("projection");
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));
    //lbl.draw(textProgram);
}

ResourcePack LoadingScene::getResources()
{
    return ResourcePack({loadingShader.get()});
}

void LoadingScene::initResources()
{
    loadingShader = rm->createResource<>(
        res::ogl::ShaderProgram("data\\shaders\\colorOnlyGui\\basic.vert",
                                "data\\shaders\\colorOnlyGui\\basic.frag",
                                "loading bar shader"), sceneName);
}
