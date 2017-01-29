#include "RotateMenu.h"
#include <math.h>
#define PI acos(-1)
USING_NS_CC;

RotateMenu::RotateMenu() {
    _isMove = false;
    _angle = 0.0;
    m_autoMove = false;
    _isClick = false;
    _canStop = true;
}
bool RotateMenu::init() {
    if (!Layer::init())
        return false;


    this->setIgnoreAnchorPointForPosition(false);
    _selectedItem = nullptr;
    Size s = Director::getInstance()->getWinSize();
    this->setContentSize(s / 3 * 1.0f);
    this->setAnchorPoint(Vec2(0.5f, 0.5f));
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(RotateMenu::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(RotateMenu::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(RotateMenu::onTouchEnded, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
};

void RotateMenu::addMenuItem(Button *item, int i) {
    item->setPosition(this->getContentSize() / 2);
    //item->setColor(Color3B::GRAY);
    this->addChild(item);
    _items.pushBack(item);
    setUnitAngle(2 * PI / _items.size());
    reset();
    updatePositionWithAnimation();
    return;
}
void RotateMenu::updatePosition() {
    auto menuSize = getContentSize();
    auto disY = menuSize.height / 8 + 35;
    auto disX = menuSize.width / 3;
    for (int i = 0; i < _items.size(); i++) {
        float x = menuSize.width / 2 + disX*sin(i*_unitAngle + getAngle());
        float y = menuSize.height / 2 - disY*cos(i*_unitAngle + getAngle());
        _items.at(i)->setPosition(Vec2(x, y));
        _items.at(i)->setLocalZOrder(-(int)y);
        //Opacity  129~255
        _items.at(i)->setOpacity(192 + 63 * cos(i*_unitAngle + getAngle()));
        _items.at(i)->setScale(0.55 + 0.25*cos(i*_unitAngle + getAngle()));
    }
    return;
}
void RotateMenu::updatePositionWithAnimation() {
    //先停止所有可能存在的动作

    for (int i = 0; i < _items.size(); i++)
        _items.at(i)->stopAllActions();
    auto menuSize = getContentSize();
    auto disY = menuSize.height / 8 - 35;
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
        auto scaleTo = ScaleTo::create(animationDuration, 0.55 + 0.25*cos(i*_unitAngle + getAngle()));
        _items.at(i)->runAction(scaleTo);
        _items.at(i)->setLocalZOrder(-(int)y);
    }
    scheduleOnce(schedule_selector(RotateMenu::actionEndCallBack), animationDuration);
    //schedule(schedule_selector(RotateMenu::stopMove),0.5f);
    return;
}
void RotateMenu::reset() {
    _angle = 0;
}
void RotateMenu::setAngle(float angle) {
    this->_angle = angle;
}
float RotateMenu::getAngle() {
    return _angle;
}
void RotateMenu::setUnitAngle(float angle) {
    _unitAngle = angle;
}
float RotateMenu::getUnitAngle() {
    return _unitAngle;
}

float RotateMenu::disToAngle(float dis) {
    float width = this->getContentSize().width / 2;
    return dis / width*getUnitAngle();
}

Button * RotateMenu::getCurrentItem() {
    if (_items.size() == 0)
        return nullptr;
    //这里实际加上了0.1getAngle(),用来防止精度丢失
    int  index = (int)((2 * PI - getAngle()) / getUnitAngle() + 0.1*getUnitAngle());
    index %= _items.size();
    return _items.at(index);
}

void RotateMenu::setClickButton(bool flag) {
    _isClick = flag;
}

bool RotateMenu::onTouchBegan(Touch* touch, Event* event) {
    m_autoMove = true;
    //先停止所有可能存在的动作
    for (int i = 0; i < _items.size(); i++)
        _items.at(i)->stopAllActions();
    if (_isClick)
        unschedule(schedule_selector(RotateMenu::autoMove));
    //if (_selectedItem)
    //	_selectedItem->setEnabled(false);
    auto position = this->convertToNodeSpace(touch->getLocation());
    auto size = this->getContentSize();
    auto rect = Rect(0, 0, size.width, size.height);
    if (rect.containsPoint(position)) {
        return true;
    }
    return false;
}
void RotateMenu::onTouchEnded(Touch* touch, Event* event) {
    auto xDelta = touch->getLocation().x - touch->getStartLocation().x;  // 这段代码是自动效验位置
//    if (disToAngle(fabs(xDelta))<getUnitAngle() / 6 && _selectedItem)
    // _selectedItem->setEnabled(true);
    if (!m_autoMove) {
        // if (_isMove == true) {
        // updatePositionWithAnimation();
        //  } else {
        //rectify(xDelta>0);
        //updatePositionWithAnimation();
        schedule(schedule_selector(RotateMenu::autoMove));
        // }
    }
    _isMove = true;
    return;
}

void RotateMenu::onTouchMoved(Touch* touch, Event* event) {
    _isMove = false;
    m_autoMove = false;
    unschedule(schedule_selector(RotateMenu::autoMove));
    auto angle = disToAngle(touch->getDelta().x);
    setAngle(getAngle() + angle);
    updatePosition();
    return;
}
void RotateMenu::rectify(bool forward) {
    auto angle = getAngle();
    while (angle<0)
        angle += PI * 2;
    while (angle>PI * 2)
        angle -= PI * 2;
    if (forward>0)
        angle = ((int)((angle + getUnitAngle() / 3 * 2) / getUnitAngle()))*getUnitAngle();
    else
        angle = ((int)((angle + getUnitAngle() / 3) / getUnitAngle()))*getUnitAngle();
    setAngle(angle);
}

void RotateMenu::actionEndCallBack(float dx) {
    _selectedItem = getCurrentItem();
    //if (_selectedItem)
    //	_selectedItem->setTouchEnabled(true);
    schedule(schedule_selector(RotateMenu::autoMove));
}
void RotateMenu::stopMove(float dt) {
    unschedule(schedule_selector(RotateMenu::autoMove));
    this->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([&]() {
        schedule(schedule_selector(RotateMenu::autoMove));
    }), nullptr));
}


void RotateMenu::autoMove(float dt) {
    auto angle = disToAngle(-1.0f);
    setAngle(getAngle() + angle);
    updatePosition();

    if (_canStopCount > 0) {
        _canStopCount = 0;
    }

    //
    int iZOrder = _items.at(0)->getLocalZOrder();
    tag = _items.at(0)->getTag();

    for (auto btn : _items) {
        int tempZOrder = btn->getLocalZOrder();
        if (tempZOrder > iZOrder) {
            tag = btn->getTag();
            iZOrder = btn->getLocalZOrder();
        }
    }

    for (auto btn : _items) {
        if (btn->getTag() == tag) {
            auto x = btn->getPositionX();
            if (x > 212 && x < 212.8) {
                if (_canStopCount < 1) {
                    tag = btn->getTag();
                    _canStopCount++;
                    unschedule(schedule_selector(RotateMenu::autoMove));
                    this->runAction(Sequence::create(CallFunc::create([&]() {
                    }), DelayTime::create(1.0f), CallFunc::create([&]() {
                    }),
                    CallFunc::create([&]() {
                        schedule(schedule_selector(RotateMenu::autoMove));
                    }), nullptr));

                    break;
                }
            }
        }
    }
}