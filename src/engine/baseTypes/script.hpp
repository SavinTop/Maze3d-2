#pragma once 

template<typename T>
class Script{
public:
    Script(T* component){this->component = component;}
    virtual void init() = 0;
    virtual void update(float delta) = 0;
    virtual void fixedUpdate() = 0;
    virtual void physicalUpdate() = 0;
private:
    T* component;
};