#include "stdafx.h"
#include "DropdownList.h"
#include "../../game/MixProject/Classes/CommonRes.h"

namespace HN {

DropdownList::DropdownList() {
}

DropdownList::~DropdownList() {
}

bool HN::DropdownList::init() {
    if (!HNLayer::init()) {
        return false;
    }
    this->ignoreAnchorPointForPosition(false);

    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(false);
    listener->onTouchBegan = CC_CALLBACK_2(DropdownList::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(DropdownList::onTouchEnded, this);
    //listener->onTouchMoved = CC_CALLBACK_2(BRNNHelpLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto _toolbarBg = Sprite::create(TOOLBAR_BG);
    setContentSize(_toolbarBg->getContentSize());

    _toolbarBg->setPosition(Vec2(getContentSize().width/2,getContentSize().height/2));
    addChild(_toolbarBg);



    //顶部和底部的空白间距总和
    int off = 70;
    int childHeight = (getContentSize().height / 2 - off) / 3;
    int halfHeight = getContentSize().height / 2;

    setBtn = AControlButton::create(TOOLBAR_SET);
    setBtn->setTag(DL_SetBtn);
    setBtn->setPosition(getContentSize().width / 2, getContentSize().height/2+  childHeight * 3);
    addChild(setBtn);

    helpBtn = AControlButton::create(TOOLBAR_HELP);
    helpBtn->setTag(DL_HelpBtn);
    helpBtn->setPosition(setBtn->getPositionX(), getContentSize().height / 2 + childHeight * 1);
    addChild(helpBtn);

    leaveBtn = AControlButton::create(TOOLBAR_LEAVE);
    leaveBtn->setTag(DL_LeaveBtn);
    leaveBtn->setPosition(setBtn->getPositionX(), getContentSize().height / 2 - childHeight * 1);
    addChild(leaveBtn);

    nextRoundOutBtn = AControlButton::create(TOOLBAR_NEXT_EXIT);
    nextRoundOutBtn->setTag(DL_NextRoundExitBtn);
    nextRoundOutBtn->setUserData((void*)false);
    nextRoundOutBtn->setPosition(setBtn->getPositionX(), getContentSize().height / 2 - childHeight * 3);
    addChild(nextRoundOutBtn);

    //CheckBox* checkbox = CheckBox::create(TOOLBAR_NEXT_EXIT, TOOLBAR_CHECKBOX);
    //addChild(checkbox);

    checkSprite = Sprite::create(TOOLBAR_CHECKBOX);
    checkSprite->setPosition(Vec2(25.0f, checkSprite->getContentSize().height*0.75f));
    checkSprite->setVisible(false);
    nextRoundOutBtn->addChild(checkSprite);

    isSelected = false;

    return true;
}

bool DropdownList::onTouchBegan(Touch *touch, Event *unused_event) {
    Point point = touch->getLocation();
    Rect rect = this->getBoundingBox();
    //HNLog::logInfo("x:%f,y:%f,w:%f,h:%f",this->getBoundingBox().getMinX(),this->getou)
    Vec2 touchPoint = this->convertToNodeSpaceAR(point);
    if (!this->getBoundingBox().containsPoint(touchPoint)) {
        //return false;
    }
    return true;
}

void DropdownList::onTouchEnded(Touch *touch, Event *unused_event) {
}

void DropdownList::changeCheckBox() {
    if (nextRoundOutBtn->getUserData() == (void*)true) {
        nextRoundOutBtn->setUserData((void*)false);
        checkSprite->setVisible(false);
        isSelected = false;
        //
    } else if (nextRoundOutBtn->getUserData() == (void*)false) {
        nextRoundOutBtn->setUserData((void*)true);
        checkSprite->setVisible(true);
        isSelected = true;
    }
    checkSprite->setVisible(isSelected);
}

bool DropdownList::isSelectedBox() {
    return isSelected;
}

void DropdownList::setSetBtnCallback(cocos2d::extension::Control::Handler handle) {
    setBtn->addTargetWithActionForControlEvents(this, handle, Control::EventType::TOUCH_UP_INSIDE);
}

void DropdownList::setLeaveBtnCallback(cocos2d::extension::Control::Handler handle) {
    leaveBtn->addTargetWithActionForControlEvents(this, handle, Control::EventType::TOUCH_UP_INSIDE);
}

void DropdownList::setNextRoundBtnCallback(cocos2d::extension::Control::Handler handle) {
    nextRoundOutBtn->addTargetWithActionForControlEvents(this, handle, Control::EventType::TOUCH_UP_INSIDE);
}

void DropdownList::setHelpBtnCallback(cocos2d::extension::Control::Handler handle) {
    helpBtn->addTargetWithActionForControlEvents(this, handle, Control::EventType::TOUCH_UP_INSIDE);
}

}