#include "ButtonTest.h"
#include "globel/ApplicationMacro.h"
#include "framework/testResource.h"
#include "ui/base/AUIButton.h"
#include "ui/base/AControlButton.h"
#include <string>

USING_NS_CC;
using namespace HN;

ButtonTests::ButtonTests() {
    ADD_TEST_CASE(BaseButtonTest);
}

//------------------------------------------------------------------
//
// BaseButtonTest
//
//------------------------------------------------------------------

BaseButtonTest::BaseButtonTest(void) {
}

BaseButtonTest::~BaseButtonTest(void) {
}


void BaseButtonTest::onEnter() {
    TestCase::onEnter();

    //第一种写法
    // auto testBtn = AButton::create();
    // testBtn->loadTextures(BRNN_TABLERES_BTN_MAKER1, BRNN_TABLERES_BTN_MAKER1,
    // BRNN_TABLERES_BTN_MAKER1);
    //第二种写法
    std::string bg = "common/button1/5.png";
    std::string title = "common/button1/17.png";
    auto uiBtn = AUIButton::create(bg, bg, bg);
    uiBtn->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    uiBtn->setPosition(Vec2(300, 300));
    uiBtn->setPressedActionEnabled(true);
    uiBtn->setTitle(title);
    uiBtn->setGray(true);
    uiBtn->setEnabled(true);
    addChild(uiBtn);

    //////////////////////////////////////////////////////////////////////////
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(bg);
    auto controlBtn = AControlButton::create(bg.c_str());
    controlBtn->setPosition(Vec2(300, 600));
    controlBtn->setPreferredSize(texture->getContentSize());
    controlBtn->setTitle(title.c_str());
    controlBtn->setGray(true);
    controlBtn->setHighlighted(true);
    addChild(controlBtn);
    //
    auto button = Button::create("test/sprite/xianduizi_1.png");
    button->setPosition(Vec2(300, 200));
    button->setPressedActionEnabled(true);
    //button->addTouchEventListener(CC_CALLBACK_2(TestCase::touchEffect, this));
    addChild(button);
}

std::string BaseButtonTest::title() const {
    return "Button Test";
}
std::string BaseButtonTest::subtitle() const {
    return "Base Button test";
}