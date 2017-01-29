#pragma once

//视差滚动层：用来表现游戏背景的视差滚动
//此层有前后两个背景

#include "cocos2d.h"

USING_NS_CC;

class ParallaxScrollingLayer: public cocos2d::Layer {
private:
    cocos2d::Sprite* m_background;
    cocos2d::Sprite* m_foreground;
    cocos2d::Size m_visibleSize;
    float m_speed = 0;

protected:
    void moveForeground();
    void moveBackgroud();

public:
    ParallaxScrollingLayer();
    virtual ~ParallaxScrollingLayer();
    CREATE_FUNC(ParallaxScrollingLayer)
    ;

    virtual bool init();
    virtual void update(float delta);
public:
    void setBackground(Sprite* background);
    void setForeground(Sprite* foreground);
    void setVisibleSize(Size size);
    void setSpeed(float speed);
};

