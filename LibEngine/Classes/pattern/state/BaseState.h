#ifndef _BASE_STATE_H_
#define _BASE_STATE_H_

#include "UI/Base/HNScene.h"

/*
状态基类
*/
class BaseState  : public HN::HNScene {
public:
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void execute() = 0;

private:
    std::string name = typeid(this).name();
};

#endif //_BASE_STATE_H_