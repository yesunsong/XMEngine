#ifndef __HN_HNScene_H__
#define __HN_HNScene_H__

#include "cocos2d.h"
USING_NS_CC;

namespace HN {

class HNScene : public Scene {
public:
    HNScene(void);
    virtual ~HNScene(void);
    static HNScene *create();

public:
    virtual bool init() override;

    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void onExitTransitionDidStart()override;
    virtual void onEnterTransitionDidFinish() override;

private:
    //是否有移动过
    bool isMoved;
    //点击屏幕上区域的次数
    unsigned int downCount;
    //点击屏幕下区域的次数
    unsigned int upCount;

private:
    void releaseLastScene(float dt);
};
};

#endif //__HN_HNScene_H__
