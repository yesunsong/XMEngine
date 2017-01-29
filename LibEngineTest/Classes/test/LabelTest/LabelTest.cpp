#include "LabelTest.h"
#include "globel/ApplicationMacro.h"
#include "framework/testResource.h"
#include "test/HNConverCode.h"
#include "globel/FontSize.h"

USING_NS_CC;
using namespace HN;

enum {
    kTagTileMap = 1,
};

LabelTests::LabelTests() {
    ADD_TEST_CASE(BaseLabelTest);
    //ADD_TEST_CASE(LabelAtlasColorTest);
}

//------------------------------------------------------------------
//
// BaseLabelTest
//
//------------------------------------------------------------------

BaseLabelTest::BaseLabelTest(void) {
}

BaseLabelTest::~BaseLabelTest(void) {
}

void BaseLabelTest::onEnter() {
    TestCase::onEnter();

    auto bankerMoneyLabel = LabelAtlas::create(":;123456789", FNT_YELLOW_THREE, 22, 28, '0');
    bankerMoneyLabel->setPosition(WIN_SIZE.width / 2, WIN_SIZE.height / 2);
    addChild(bankerMoneyLabel);

    auto myMoneyLabel = LabelAtlas::create(":;123456789", FNT_BLUE_ONE, 22, 28, '0');
    myMoneyLabel->setPosition(bankerMoneyLabel->getPositionX(),bankerMoneyLabel->getPositionY() -bankerMoneyLabel->getContentSize().height);
    addChild(myMoneyLabel);

    testGBK2UTF8();
}

void BaseLabelTest::testGBK2UTF8() {
    auto label = Label::createWithTTF("", DEFAULT_FONT, FONT_SIZE_25);
    label->setPosition(Vec2(WIN_SIZE.width / 2, WIN_SIZE.height / 2));
    addChild(label);

    label->setString(GBKToUtf8("中国人"));
    //label->setString(GetText("tuoguan_tips")); // TODO tuoguan_tips这个为什么没有显示出来

    auto label1 = Label::createWithTTF("", DEFAULT_FONT, FONT_SIZE_25);
    label1->setPosition(Vec2(WIN_SIZE.width / 2, WIN_SIZE.height / 2 - 100));
    addChild(label1);
    label1->setString(StringUtils::format(GetText("union_banker"), 1)); // TODO tuoguan_tips这个为什么没有显示出来
}

std::string BaseLabelTest::title() const {
    return "Label Test";
}

std::string BaseLabelTest::subtitle() const {
    return "Base Label test";
}