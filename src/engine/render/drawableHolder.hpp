#pragma once 

#include "drawable.hpp"

class DrawableHolder : public Drawable{
public:
    DrawableHolder(){};
    DrawableHolder(Drawable* target_);
    void __draw(oglw::Shader& shader) override;
    void setTarget(Drawable* target_);
    Drawable* getTarget();
private:
    Drawable* target;
};