/*
 * HRocker.cpp
 *
 *  Created on: 2015年8月19日
 *      Author: yss
 */

#include "HRocker.h"

HRocker::HRocker() {
}

HRocker::~HRocker() {
}

HRocker* HRocker::create(Vec2 aPoint, float aRadius, Sprite* aJsSprite,
                         Sprite* aJsBg, bool _isFollowRole) {
    HRocker *ret = new (std::nothrow) HRocker();
    if (ret
            && ret->initWithCenter(aPoint, aRadius, aJsSprite, aJsBg,
                                   _isFollowRole)) {
        ret->autorelease();
        return ret;
    } else {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool HRocker::initWithCenter(Vec2 aPoint, float aRadius, Sprite* aJsSprite,
                             Sprite* aJsBg, bool _isFollowRole) {
    active = false;
    radius = aRadius;
    isFollowRole = _isFollowRole;
    if (!_isFollowRole) {
        centerPoint = aPoint;
    } else {
        centerPoint = Vec2::ZERO;
    }
    currentPoint = centerPoint;
    jsSprite = aJsSprite;
    jsSprite->setPosition(centerPoint);
    aJsBg->setPosition(centerPoint);
    aJsBg->setTag(88);
    this->addChild(aJsBg);
    this->addChild(jsSprite);

    if (isFollowRole) {
        this->setVisible(false);
    }
    this->Active(); //激活摇杆

    EventListenerTouchOneByOne* _listener =
        EventListenerTouchOneByOne::create();
    _listener->onTouchBegan = CC_CALLBACK_2(HRocker::onTouchBegan,this);
    _listener->onTouchMoved = CC_CALLBACK_2(HRocker::onTouchMoved,this);
    _listener->onTouchEnded = CC_CALLBACK_2(HRocker::onTouchEnded,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
    return true;
}

void HRocker::updatePos(float dt) {
    Vec2 tmp(currentPoint);
    tmp.subtract(jsSprite->getPosition());
    tmp *= 0.5;
    tmp.add(jsSprite->getPosition());
    jsSprite->setPosition(tmp);
}

void HRocker::Active() {
    if (!active) {
        active = true;
        schedule(schedule_selector(HRocker::updatePos)); //添加刷新函数
//		CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0,
//				false); //添加触摸委托
    }
}

void HRocker::Inactive() {
    if (active) {
        active = false;
        this->unschedule(schedule_selector(HRocker::updatePos)); //删除刷新
//		CCTouchDispatcher::sharedDispatcher()->removeDelegate(this); //删除委托
    }
}

bool HRocker::onTouchBegan(Touch* touch, Event* event) {
    if (!active) {
        return false;
    }
    this->setVisible(true);
    Vec2 touchPoint = touch->getLocationInView();
    touchPoint = Director::getInstance()->convertToGL(touchPoint);
    if (!isFollowRole) {
        if (touchPoint.distance(centerPoint) > radius) {
            return false;
        }
    }
    currentPoint = touchPoint;
    if (isFollowRole) {
        centerPoint = currentPoint;
        jsSprite->setPosition(currentPoint);
        this->getChildByTag(88)->setPosition(currentPoint);
    }
    return true;
}

void HRocker::onTouchMoved(Touch* touch, Event* event) {
    Vec2 touchPoint = touch->getLocationInView();
    touchPoint = Director::getInstance()->convertToGL(touchPoint);
    if (touchPoint.distance(centerPoint) > radius) {
        touchPoint.subtract(centerPoint);
        touchPoint.normalize();
        touchPoint *= radius;
        touchPoint.add(centerPoint);
        currentPoint = touchPoint;
//		currentPoint = ccpAdd(centerPoint,
//				ccpMult(ccpNormalize(ccpSub(touchPoint, centerPoint)), radius));
    } else {
        currentPoint = touchPoint;
    }
}

void HRocker::onTouchEnded(Touch* touch, Event* event) {
    currentPoint = centerPoint;
    if (isFollowRole) {
        this->setVisible(false);
    }
}

Vec2 HRocker::getDirection() {
    Vec2 tmp(centerPoint);
    tmp.subtract(currentPoint);
    tmp.normalize();
    return tmp;
}

float HRocker::getVelocity() {
    return centerPoint.distance(currentPoint);
}
