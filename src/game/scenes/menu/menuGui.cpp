#include "menuGui.hpp"


void MenuGui::load() 
{
    r_pack.load();
}

void MenuGui::unload() 
{
    r_pack.unload();
}

void MenuGui::mouseInput(int x, int y, bool lb) 
{
    if(!currentWindow) return;
    currentWindow->__mouseMove(x,h-y);
    if(lb)
        currentWindow->__leftMouseBtnDown(x,h-y);
}

std::vector<Drawable*> MenuGui::getElements() 
{
    if(!currentWindow) return {};
    return currentWindow->getDrawableChildArr();
}

std::vector<Drawable*> MenuGui::getDrawableChildrenRecurs(GuiObject* curr) 
{
    if(!curr) return {};
    std::vector<Drawable*> temp;
    temp.push_back(curr);
    for(auto el:curr->getChildArr())
    {
        auto conc = getDrawableChildrenRecurs(el);
        temp.reserve(temp.size()+conc.size());
        temp.insert(temp.end(), conc.begin(), conc.end());
    }
    return temp;
}

void MenuGui::back_click() 
{
    currentWindow = &main;
}

MenuGui::MenuGui(int w, int h, ResourceManager* rm) 
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
    testlabel.setPosition(w/2,h/2);
    testlabel.setSize(w,main_endless_button.height());
    testlabel.setText("lol kek cheburec");
    testlabel.setTextAlign(textAlign::Right);
}

void MenuGui::draw() 
{
    guiShader->bind();
    unsigned viewId = guiShader->getUniformLocation("view");
    unsigned projectionId = guiShader->getUniformLocation("projection");
    unsigned modelId = guiShader->getUniformLocation("model");
    unsigned colorId = guiShader->getUniformLocation("color");
    glm::mat4 view = glm::mat4(1.0f);
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
    glm::mat4 projection(1); 
    projection = glm::ortho(0.0f,(float)w,0.0f,(float)h,0.0f,100.0f);
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));

    //mesh->draw(program);
    for(auto el:getElements())
        el->draw(guiShader->getProgram());

    guiShader->unbind();

    auto& textShader = guiText_getTextShader();
    textShader.bind();
    projectionId = textShader.getUniformLocation("projection");
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projection));
    testlabel.draw(textShader);
}

MenuGui::MenuGui() 
{
    this->w = 0;
    this->h = 0;
    this->rm = 0;
    currentWindow = nullptr;
}
