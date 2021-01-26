#include "shadow_new.hpp"

void Shadow_New::gl_init(ObjectMazeMap* omm,oglw::Shader* shadowProgram,
 float res, glm::vec3 lightPosition, int s_w, int s_h) 
{
    this->omm = omm;
    this->res = res;
    this->shadowProgram = shadowProgram;
    this->lightPosition = lightPosition;
    this->s_w = s_w;
    this->s_h = s_h;
    lastUpdated = 0;

    this->field.resize(omm->width());
    for(auto& el:this->field)
        el.resize(omm->height());
}

sh_block& Shadow_New::getBlock(int x, int y) 
{
    if(x>=omm->width() || y>=omm->height() || x<0 || y<0)
    {
        std::cout<<"trying to access wrong shadow block\n";
        return field[0][0];
    }
    auto& curr = field[x][y];
    curr.lastUpdate = glfwGetTime();
    curr.res = res;
    if(curr.loaded) return curr;
    
    update_stack.push(std::make_pair(x,y));

    return curr;
}

void Shadow_New::update() 
{
    while(update_stack.size())
    {
        auto curr = update_stack.top();
        int x = curr.first;
        int y = curr.second;
        initializeBlock(x,y);
        redrawBlock(x,y);
        update_stack.pop();
    }
    if(glfwGetTime() - lastUpdated > 3)
    {
        for (int i = 0; i < omm->height(); i++)
        for (int j = 0; j < omm->width(); j++)
        {
            auto& curr = field[j][i];
            if(!curr.loaded) continue;
            if(glfwGetTime()-curr.lastUpdate>3)
                clearBlock(j,i);
        }
        lastUpdated = glfwGetTime();
    }
    
}

void Shadow_New::clearAll() 
{
    for (int i = 0; i < omm->height(); i++)
        for (int j = 0; j < omm->width(); j++)
            clearBlock(j,i);
}

void Shadow_New::forceUpdate(int x, int y) 
{
    if(x>=omm->width() || y>=omm->height() || x<0 || y<0) return;
    clearBlock(x,y);
    update_stack.push(std::make_pair(x,y));
}

void Shadow_New::initializeBlock(int x, int y) 
{
    if(x>=omm->width() || y>=omm->height() || x<0 || y<0)
    {
        std::cout<<"trying to access wrong shadow block\n";
        return;
    }
    auto& curr = field[x][y];
    if(curr.loaded) return;
    curr.depthMapFBO = 0;
    curr.depthMapTex = 0;

    glGenFramebuffers(1, &curr.depthMapFBO);
    glGenTextures(1, &curr.depthMapTex);
    glBindTexture(GL_TEXTURE_2D, curr.depthMapTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
             curr.res, curr.res, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glBindFramebuffer(GL_FRAMEBUFFER, curr.depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, curr.depthMapTex, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);  

    curr.loaded = true;

    if(!curr.depthMapFBO || !curr.depthMapTex)
        curr.loaded = false;
    
    if(!curr.loaded)
        std::cout<<"cant create shadow fbo\n";

    CheckGLError();
}

void Shadow_New::redrawBlock(int x, int y) 
{
    if(x>=omm->width() || y>=omm->height() || x<0 || y<0)
    {
        std::cout<<"trying to access wrong shadow block\n";
        return;
    }
    auto& curr = field[x][y];
    if(!curr.loaded) return;

    glCullFace(GL_FRONT);
    shadowProgram->bind();
    unsigned int lsm_id = shadowProgram->getUniformLocation("lightSpaceMatrix");

    float h_width = 10;
    float h_height = 10;

    glm::vec3 center{x*8, -3, y*8};

    glm::mat4 lightProjection = glm::ortho(-h_width, h_width, -h_height, h_height, 1.0f, 200.0f);
    glm::mat4 lightView = glm::lookAt(lightPosition+center,
                                       center,
                                       glm::vec3(0.0f, 1.0f, 0.0f));
    curr.lightSpaceMatrix = lightProjection * lightView;
    glUniformMatrix4fv(lsm_id, 1, false, glm::value_ptr(curr.lightSpaceMatrix));
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glViewport(0, 0, curr.res, curr.res);
    glBindFramebuffer(GL_FRAMEBUFFER, curr.depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    for (int i = y-2; i <= y+2; i++)
        for (int j = x-2; j <= x+2; j++)
        if(auto obj = omm->get(j, i)){
            obj->model.draw(*shadowProgram);
            auto t = obj->child;
            if(t.get()) 
                t->draw(*shadowProgram);
        }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, s_w, s_h);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CheckGLError();
    glCullFace(GL_BACK);
}

void Shadow_New::clearBlock(int x, int y) 
{
    auto& curr = field[x][y];
    if(!curr.loaded) return;
    glDeleteTextures(1, &curr.depthMapTex);
    glDeleteFramebuffers(1, &curr.depthMapFBO);
    curr.loaded = false;
}
