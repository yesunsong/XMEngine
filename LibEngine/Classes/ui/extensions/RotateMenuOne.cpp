#include "RotateMenuOne.h"
#include <math.h>
#define PI acos(-1)
USING_NS_CC;
bool RotateMenuOne::init() {
    if (!Layer::init())
        return false;
    _angle = 0.0;
    this->setIgnoreAnchorPointForPosition(false);
    _selectedItem = nullptr;
    Size s = Director::getInstance()->getWinSize();
    this->setContentSize(s / 3 * 2);
    this->setAnchorPoint(Vec2(0.5f, 0.5f));
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(RotateMenuOne::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(RotateMenuOne::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(RotateMenuOne::onTouchEnded, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
};

void RotateMenuOne::addMenuItem(cocos2d::MenuItem *item) {
    item->setPosition(this->getContentSize() / 2);
    this->addChild(item);
    _items.pushBack(item);
    setUnitAngle(2 * PI / _items.size());
    reset();
    updatePositionWithAnimation();
    return;
}
void RotateMenuOne::updatePosition() {
    auto menuSize = getContentSize();
    auto disY = menuSize.height / 8;
    auto disX = menuSize.width / 3;
    for (int i = 0; i < _items.size(); i++) {
        float x = menuSize.width / 2 + disX*sin(i*_unitAngle + getAngle());
        float y = menuSize.height / 2 - disY*cos(i*_unitAngle + getAngle());
        _items.at(i)->setPosition(Vec2(x, y));
        _items.at(i)->setLocalZOrder(-(int)y);
        //Opacity  129~255
        _items.at(i)->setOpacity(192 + 63 * cos(i*_unitAngle + getAngle()));
        _items.at(i)->setScale(0.75 + 0.25*cos(i*_unitAngle + getAngle()));
    }
    return;
}
void RotateMenuOne::updatePositionWithAnimation() {
    //先停止所有可能存在的动作
    for (int i = 0; i < _items.size(); i++)
        _items.at(i)->stopAllActions();
    auto menuSize = getContentSize();
    auto disY = menuSize.height / 8;
    auto disX = menuSize.width / 3;
    for (int i = 0; i < _items.size(); i++) {
        float x = menuSize.width / 2 + disX*sin(i*_unitAngle + getAngle());
        float y = menuSize.height / 2 - disY*cos(i*_unitAngle + getAngle());
        auto moveTo = MoveTo::create(animationDuration, Vec2(x, y));
        _items.at(i)->runAction(moveTo);
        //Opacity  129~255
        auto fadeTo = FadeTo::create(animationDuration, (192 + 63 * cos(i*_unitAngle + getAngle())));
        _items.at(i)->runAction(fadeTo);
        //缩放比例  0.5~1
        auto scaleTo = ScaleTo::create(animationDuration, 0.75 + 0.25*cos(i*_unitAngle + getAngle()));
        _items.at(i)->runAction(scaleTo);
        _items.at(i)->setLocalZOrder(-(int)y);
    }
    scheduleOnce(schedule_selector(RotateMenuOne::actionEndCallBack), animationDuration);
    return;
}
void RotateMenuOne::reset() {
    _angle = 0;
}
void RotateMenuOne::setAngle(float angle) {
    this->_angle = angle;
}
float RotateMenuOne::getAngle() {
    return _angle;
}
void RotateMenuOne::setUnitAngle(float angle) {
    _unitAngle = angle;
}
float RotateMenuOne::getUnitAngle() {
    return _unitAngle;
}

float RotateMenuOne::disToAngle(float dis) {
    float width = this->getContentSize().width / 2;
    return dis / width*getUnitAngle();
}

MenuItem * RotateMenuOne::getCurrentItem() {
    if (_items.size() == 0)
        return nullptr;
    //这里实际加上了0.1getAngle(),用来防止精度丢失
    int  index = (int)((2 * PI - getAngle()) / getUnitAngle() + 0.1*getUnitAngle());
    index %= _items.size();
    return _items.at(index);
}

bool RotateMenuOne::onTouchBegan(Touch* touch, Event* event) {
    //先停止所有可能存在的动作
    for (int i = 0; i < _items.size(); i++)
        _items.at(i)->stopAllActions();
    if (_selectedItem)
        _selectedItem->unselected();
    auto position = this->convertToNodeSpace(touch->getLocation());
    auto size = this->getContentSize();
    auto rect = Rect(0, 0, size.width, size.height);
    if (rect.containsPoint(position)) {
        return true;
    }
    return false;
}

void RotateMenuOne::onTouchEnded(Touch* touch, Event* event) {
    auto xDelta = touch->getLocation().x - touch->getStartLocation().x;
    rectify(xDelta > 0);
    if (disToAngle(fabs(xDelta)) < getUnitAngle() / 6 && _selectedItem)
        _selectedItem->activate();
    updatePositionWithAnimation();
    return;
}

void RotateMenuOne::onTouchMoved(Touch* touch, Event* event) {
    auto angle = disToAngle(touch->getDelta().x);
    setAngle(getAngle() + angle);
    updatePosition();
    return;
}

void RotateMenuOne::rectify(bool forward) {
    auto angle = getAngle();
    while (angle < 0)
        angle += PI * 2;
    while (angle > PI * 2)
        angle -= PI * 2;
    if (forward > 0)
        angle = ((int)((angle + getUnitAngle() / 3 * 2) / getUnitAngle()))*getUnitAngle();
    else
        angle = ((int)((angle + getUnitAngle() / 3) / getUnitAngle()))*getUnitAngle();
    setAngle(angle);
}

void RotateMenuOne::actionEndCallBack(float dx) {
    _selectedItem = getCurrentItem();
    if (_selectedItem)
        _selectedItem->selected();
}