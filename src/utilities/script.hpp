#pragma once

template<typename Component>
class Script{
    protected:
    Component _daddy;
    public:
    Script(Component _daddy){this->_daddy = _daddy;};
    virtual void Start() = 0;
    virtual void Update(float delta) = 0;
};