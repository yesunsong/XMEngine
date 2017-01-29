#include "CycScrollViewTest.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/extensions/CycScrollView.h"
USING_NS_CC;

CycScrollViewTests::CycScrollViewTests() {
    ADD_TEST_CASE(BaseCycScrollViewTest);
}

//------------------------------------------------------------------
//
// BaseCycScrollViewTest
//
//------------------------------------------------------------------

BaseCycScrollViewTest::BaseCycScrollViewTest(void) {
}

BaseCycScrollViewTest::~BaseCycScrollViewTest(void) {
}

void BaseCycScrollViewTest::onEnter() {
    TestCase::onEnter();

    std::vector<Button*> _vec;
    for (int i = 0; i < 6; i++) {
        char str[50] = { 0 };
        sprintf(str, "test/gameItemRes/%d.png", 11100200);
        auto spr = Sprite::create("test/gameItemRes/11100200.png");

        auto button = Button::create(str, str, str);
        button->setSwallowTouches(false);
        button->setPressedActionEnabled(false);
        button->ignoreContentAdaptWithSize(false);
        button->setAnchorPoint(Point(0.5, 0.5));
        button->setContentSize(spr->getContentSize());
        //button->addTouchEventListener(CC_CALLBACK_2(GameLists::enterRoomEventCallBack, this));
        button->setTag(i);
        _vec.push_back(button);
    }

    CycScrollView* cycScrollView = CycScrollView::create();
    cycScrollView->loadScrollView(_vec, 15);
    cycScrollView->setFirstIndex(5);
    cycScrollView->setPosition(Vec2(0, 150));
    addChild(cycScrollView);
}

std::string BaseCycScrollViewTest::title() const {
    return "Base CycScrollView Test";
}

std::string BaseCycScrollViewTest::subtitle() const {
    return "Base CycScrollView Test";
}