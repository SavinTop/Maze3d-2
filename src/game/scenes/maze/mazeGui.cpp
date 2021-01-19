#include "mazeGui.hpp"


void MazeGui::start() 
{
    initBeg();
    initDebug();
    initTimer();
    currentWindow = &beg;
}

void MazeGui::draw() 
{
    glDisable(GL_DEPTH_TEST);
    auto &textShader = guiText_getTextShader();
    
    oglw::Shader* currShader = &textShader;

    for (auto el : getElements())
    {
        guiShaderType curr = el->getShaderType();

            if (curr == guiShaderType::textureShader)
            {
                guiShader->bind();
                unsigned viewId = guiShader->getUniformLocation("view");
                unsigned projectionId = guiShader->getUniformLocation("projection");
                unsigned modelId = guiShader->getUniformLocation("model");
                glm::mat4 view = glm::mat4(1.0f);
                //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
                glm::mat4 projection(1);
                projection = glm::ortho(0.0f, (float)w, 0.0f, (float)h, 0.0f, 100.0f);
                glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
                glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));
                currShader = &guiShader->getProgram();
            }
            else if (curr == guiShaderType::textShader)
            {
                textShader.bind();
                glm::mat4 projection(1);
                projection = glm::ortho(0.0f, (float)w, 0.0f, (float)h, 0.0f, 100.0f);
                unsigned projectionId = textShader.getUniformLocation("projection");
                glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));
                currShader = &textShader;
            }

        el->draw(*currShader);
    }
    glEnable(GL_DEPTH_TEST);
}

void MazeGui::load() 
{
    
}

void MazeGui::unload() 
{
    
}

void MazeGui::mouseInput(int x, int y, bool lb) 
{
    if (!currentWindow) return;
    currentWindow->__mouseMove(x, h - y);
    if (lb)
        currentWindow->__leftMouseBtnDown(x, h - y);
}

void MazeGui::initDebug() 
{
    debug = GuiWindow(w,h);
    debug_fbox = FullscreenBox(nullptr,w,h);
    debug_fbox.setParent(&debug);

    debug_playerX.setParent(&debug_fbox);
    debug_playerX.setPosition(-0.8f, 0.9f);
    debug_playerX.setSize(0.2f, 0.1f);
    debug_playerX.setTextAlign(textAlign::Left);

    debug_playerY.setParent(&debug_fbox);
    debug_playerY.setPosition(-0.8f, 0.7f);
    debug_playerY.setSize(0.2f, 0.1f);
    debug_playerY.setTextAlign(textAlign::Left);

    auto temp = getChildrenRecurs(&debug);
    debug.setDrawableChildArr(temp);
}

void MazeGui::initBeg() 
{
    beg = GuiWindow(w,h);
    beg_fbox = FullscreenBox(nullptr,w,h);
    beg_fbox.setParent(&beg);

    const float downSpace = 0.15;

    beg_mazemap_test = Button(nullptr,  beg_mazemap_tex.get(), beg_mazemap_tex.get(),0.1);
    beg_mazemap_test.setParent(&beg_fbox);
    beg_mazemap_test.setPosition(0.0f,0.0f+downSpace);
    beg_mazemap_test.setSize(1.0f-downSpace,1.0f-downSpace);

    beg_ok = Button(nullptr, beg_ok_idle.get(), beg_ok_active.get());
    beg_ok.setParent(&beg_fbox);
    beg_ok.setSize(0.3f,0.09f);
    beg_ok.setPosition(0.0f,-0.85f);

    auto temp = getChildrenRecurs(&beg);
    beg.setDrawableChildArr(temp);
}

void MazeGui::initTimer() 
{
    timer = GuiWindow(w,h);
    timer_fbox = FullscreenBox(nullptr,w,h);
    timer_fbox.setParent(&timer);

    timer_time.setParent(&timer_fbox);
    timer_time.setPosition(0.0f, -0.93f);
    timer_time.setSize(2.0f, 0.05f);
    timer_time.setTextAlign(textAlign::Center);
    timer_time.setColor(glm::vec3(Color::getOglColor(Color::rgba(255,255,0,255))));

    auto temp = getChildrenRecurs(&timer);
    timer.setDrawableChildArr(temp);
}

void MazeGui::debug_setDebugPlayerPos(float x, float y) 
{
    debug_playerX.setText("x: "+std::to_string(x));
    debug_playerY.setText("y: "+std::to_string(y));
}

void MazeGui::timer_setTime(float t) 
{
    time_value = t;
    timer_time.setText(std::to_string(t));
}

void MazeGui::setMazeMap(std::shared_ptr<res::ogl::Texture> mazeTexture) 
{
    beg_mazemap_tex = mazeTexture;
}

void MazeGui::setOkCallback(std::function<void(void)> click) 
{
    beg_ok.setClickCallback(click);
}

void MazeGui::InitializeSubResources(std::string groupName) 
{
    this->guiShader = rm->createResource(res::ogl::ShaderProgram("data\\shaders\\basicGui\\basic.vert","data\\shaders\\basicGui\\basic.frag", "guiProgram"),groupName);
    this->beg_ok_idle = rm->createResource(res::ogl::Texture(spriteDirectory+"buttons\\ok_idle.png"),groupName);
    this->beg_ok_active = rm->createResource(res::ogl::Texture(spriteDirectory+"buttons\\ok_active.png"),groupName);
    this->beg_mazemap_savin_tex = rm->createResource(res::ogl::Texture("data\\savin.jpg"), groupName);
}

ResourcePack& MazeGui::getResources() 
{
    r_pack = ResourcePack({guiShader.get(), beg_ok_active.get(), beg_ok_idle.get(), beg_mazemap_savin_tex.get()});
    return r_pack;
}

std::vector<GuiObject*> MazeGui::getElements() 
{
    if (!currentWindow)
        return {};
    return currentWindow->getDrawableChildArr();
}

std::vector<GuiObject*> MazeGui::getChildrenRecurs(GuiObject* curr) 
{
    if (!curr)
        return {};
    std::vector<GuiObject *> temp;
    temp.push_back(curr);
    for (auto el : curr->getChildArr())
    {
        auto conc = getChildrenRecurs(el);
        temp.reserve(temp.size() + conc.size());
        temp.insert(temp.end(), conc.begin(), conc.end());
    }
    return temp;
}

MazeGui::MazeGui() 
{
    
}

MazeGui::MazeGui(int w, int h, ResourceManager* rm) 
{
    this->w = w;
    this->h = h;
    this->rm = rm;
    currentWindow = nullptr;
}

MazeGui::~MazeGui() 
{
}
