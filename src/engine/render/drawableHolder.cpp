#include "drawableHolder.hpp"

DrawableHolder::DrawableHolder(Drawable* target_) 
{
    setTarget(target_);
}

void DrawableHolder::__draw(oglw::Shader& shader) 
{
    if(target)
        target->__draw(shader);
}

void DrawableHolder::setTarget(Drawable* target_) 
{
    this->target = target_;
}

Drawable* DrawableHolder::getTarget() 
{
    return target;
}
