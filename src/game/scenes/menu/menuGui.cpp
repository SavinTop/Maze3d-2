#include "menuGui.hpp"

void MenuGui::load()
{
    
}

void MenuGui::unload()
{
    
}

void MenuGui::mouseInput(int x, int y, bool lb)
{
    if (!currentWindow) return;
    currentWindow->__mouseMove(x, h - y);
    if (lb && lb!=lastMouseLeftButton)
        currentWindow->__leftMouseBtnDown(x, h - y);
    lastMouseLeftButton = lb;
}

std::vector<GuiObject *> MenuGui::getElements()
{
    if (!currentWindow)
        return {};
    return currentWindow->getDrawableChildArr();
}

std::vector<GuiObject *> MenuGui::getChildrenRecurs(GuiObject *curr)
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

void MenuGui::back_click()
{
    currentWindow = &main;
}

MenuGui::MenuGui(int w, int h, ResourceManager *rm)
{
    this->w = w;
    this->h = h;
    this->rm = rm;
    currentWindow = nullptr;
}

void MenuGui::start()
{
    initMain();
    initEndless();
    currentWindow = &main;
}

void MenuGui::draw()
{
    auto &textShader = guiText_getTextShader();
    
    guiShaderType last = guiShaderType::COUNT;
    oglw::Shader* currShader = &textShader;

    for (auto el : getElements())
    {
        guiShaderType curr = el->getShaderType();

        if (curr != last)
        {
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
        }

        el->draw(*currShader);

        last = curr;
    }
}

MenuGui::MenuGui()
{
    this->w = 0;
    this->h = 0;
    this->rm = 0;
    currentWindow = nullptr;
    lastMouseLeftButton = false;
}
