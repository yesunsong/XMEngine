#include "BaseState.h"
#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

/*
状态管理类
*/
class StateManager {
public:
    void start(BaseState* state);
    void setState(BaseState* state, bool isAnimated = true);
    static StateManager* getInstance();

private:
    BaseState* curState;
    StateManager();
    virtual ~StateManager();

    static StateManager* manager;
};
#endif //_STATEMANAGER_H_