/*
 * HRocker.h
 *
 *  Created on: 2015年8月19日
 *      Author: yss
 */

#ifndef HROCKER_H_
#define HROCKER_H_

#include "cocos2d.h"

USING_NS_CC;

class HRocker: cocos2d::Layer {
public:
    HRocker();
    virtual ~HRocker();

public:
    static HRocker* create(Vec2 aPoint, float aRadius, Sprite* aJsSprite,
                           Sprite* aJsBg, bool _isFollowRole);
    /**
     * 启动摇杆
     */
    void Active();
    /**
     * 解除摇杆
     */
    void Inactive();

private:
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);

private:
    /* 初始化方法
     *    第一个参数aPoint：摇杆中心点的坐标
     *    第二个参数aRadius: 摇杆的半径
     *    第三个参数aJsSprite :摇杆控制点的资源
     *    第四个参数aJsBg: 摇杆背景的资源
     *    第五个参数isFollowRole：是否让摇杆控制点永远跟随用户触屏点
     */
    bool initWithCenter(Vec2 aPoint, float aRadius, Sprite* aJsSprite,
                        Sprite* aJsBg, bool _isFollowRole);
    Sprite *jsSprite;
    /**
     * 摇杆中心
     */
    Vec2 centerPoint;
    /**
     *摇杆当前位置
     */
    Vec2 currentPoint;
    /**
     * 是否激活摇杆
     */
    bool active;
    /**
     * 摇杆半径
     */
    float radius;
    /**
     * 是否跟随用户点击
     */
    bool isFollowRole;
    /**
     * 摇杆方位
     */
    Vec2 getDirection();
    /**
     * 摇杆力度
     */
    float getVelocity();

    void updatePos(float dt);
};

#endif /* HROCKER_H_ */
