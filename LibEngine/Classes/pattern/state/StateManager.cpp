#include "StateManager.h"

//在此处初始化
StateManager* StateManager::manager = nullptr;
StateManager* StateManager::getInstance() {
    return manager;
}

StateManager::StateManager() {
    manager = this;
}

StateManager::~StateManager() {
    manager = nullptr;
}

void StateManager::start(BaseState* state) {
    curState = state;
    state->enter();
    state->execute();
    Director::getInstance()->runWithScene(state);
}

void StateManager::setState(BaseState* state,bool isAnimated) {
    if (curState) {
        curState->exit();
    }

    curState = state;
    if (state) {
        state->enter();
        state->execute();

        if (isAnimated) {
            Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3f, state));
        } else {
            Director::getInstance()->replaceScene(state);
        }
    }
}

