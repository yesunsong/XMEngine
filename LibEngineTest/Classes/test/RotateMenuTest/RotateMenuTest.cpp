#include "RotateMenuTest.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/extensions/RotateMenu.h"
#include "globel/ApplicationMacro.h"
#include "ui/extensions/RotateMenuOne.h"
USING_NS_CC;

RotateMenuTests::RotateMenuTests() {
    ADD_TEST_CASE(BaseRotateMenuTest);
    ADD_TEST_CASE(RotateMenuOneTest);
}

//------------------------------------------------------------------
//
// BaseRotateMenuTest
//
//------------------------------------------------------------------

BaseRotateMenuTest::BaseRotateMenuTest(void) {
}

BaseRotateMenuTest::~BaseRotateMenuTest(void) {
}

void BaseRotateMenuTest::onEnter() {
    TestCase::onEnter();

    RotateMenu* menu = RotateMenu::create();
    menu->setPosition(Vec2(WIN_SIZE.width / 4 * 3, WIN_SIZE.height / 4 * 2.0f + 30.0));
    this->addChild(menu, 2);
    //
    for (int i = 0; i < 6; i++) {
        char farmPath[50] = { 0 };
        sprintf(farmPath, "test/gameItemRes/%d.png", 10100003);
        auto button = Button::create(farmPath, farmPath);
        auto size = button->getContentSize();
        button->setPosition(Vec2(0 - WIN_SIZE.width, (WIN_SIZE.height *0.5f + (1.5f*size.height + 20 + 10) - i *(size.height + 20) - size.height*0.5f)));
        //button->addTouchEventListener(CC_CALLBACK_2(GameType::enterGameCallBack, this));
        button->setTouchEnabled(true);
        button->setSwallowTouches(true);
        button->setPressedActionEnabled(false);
        button->ignoreContentAdaptWithSize(false);
        menu->addMenuItem(button, i);
    }
}

std::string BaseRotateMenuTest::title() const {
    return "Base CycScrollView Test";
}

std::string BaseRotateMenuTest::subtitle() const {
    return "Base CycScrollView Test";
}


//------------------------------------------------------------------
//
// RotateMenuOneTest
//
//------------------------------------------------------------------

RotateMenuOneTest::RotateMenuOneTest(void) {
}

RotateMenuOneTest::~RotateMenuOneTest(void) {
}

void RotateMenuOneTest::onEnter() {
    TestCase::onEnter();

    auto item1 = MenuItemImage::create("test/gameItemRes/11100600.png", "test/gameItemRes/11100600.png", CC_CALLBACK_1(RotateMenuOneTest::menuItem1Callback, this));
    auto item2 = MenuItemImage::create("test/gameItemRes/11105102.png", "test/gameItemRes/11105102.png", CC_CALLBACK_1(RotateMenuOneTest::menuItem2Callback, this));
    auto item3 = MenuItemImage::create("test/gameItemRes/11100200.png", "test/gameItemRes/11100200.png", CC_CALLBACK_1(RotateMenuOneTest::menuItem3Callback, this));
    auto item4 = MenuItemImage::create("test/gameItemRes/11105103.png", "test/gameItemRes/11105103.png", CC_CALLBACK_1(RotateMenuOneTest::menuItem4Callback, this));
    auto item5 = MenuItemImage::create("test/gameItemRes/11105100.png", "test/gameItemRes/11105100.png", CC_CALLBACK_1(RotateMenuOneTest::menuItem5Callback, this));

    RotateMenuOne *menu = RotateMenuOne::create();

    menu->addMenuItem(item1);
    menu->addMenuItem(item2);
    menu->addMenuItem(item3);
    menu->addMenuItem(item4);
    menu->addMenuItem(item5);

    menu->setPosition(WIN_SIZE / 2);
    this->addChild(menu, 2);
}

void RotateMenuOneTest::menuItem1Callback(cocos2d::Ref* pSender) {

}
void RotateMenuOneTest::menuItem2Callback(cocos2d::Ref* pSender) {

}
void RotateMenuOneTest::menuItem3Callback(cocos2d::Ref* pSender) {

}
void RotateMenuOneTest::menuItem4Callback(cocos2d::Ref* pSender) {

}
void RotateMenuOneTest::menuItem5Callback(cocos2d::Ref* pSender) {
    ;
}

std::string RotateMenuOneTest::title() const {
    return "RotateMenu Test";
}

std::string RotateMenuOneTest::subtitle() const {
    return "RotateMenuOne Test";
}