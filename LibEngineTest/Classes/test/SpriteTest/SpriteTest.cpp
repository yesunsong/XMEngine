#include "SpriteTest.h"

SpriteTests::SpriteTests() {
    ADD_TEST_CASE(HNSpriteTest);
}


//------------------------------------------------------------------
//
// BaseSpriteTest
//
//------------------------------------------------------------------

BaseSpriteTest::BaseSpriteTest(void) {
}

BaseSpriteTest::~BaseSpriteTest(void) {
}

std::string BaseSpriteTest::title() const {
    return "BaseSprite Test";
}
std::string BaseSpriteTest::subtitle() const {
    return "No title";
}


//------------------------------------------------------------------
//
// HNSpriteTest
//
//------------------------------------------------------------------

void HNSpriteTest::onEnter() {
    TestCase::onEnter();

    //auto child = Sprite::create(s_pathGrossini);
    //child->setPosition(VisibleRect::center());
    //addChild(child, 1, kTagGrossini);

    ////Sum of all action's duration is 1.5 second.
    //child->runAction(RotateBy::create(1.5f, 90));
    //child->runAction(Sequence::create(
    //	DelayTime::create(1.4f),
    //	FadeOut::create(1.1f),
    //	nullptr)
    //	);

    ////After 1.5 second, self will be removed.
    //child->runAction(Sequence::create(
    //	DelayTime::create(1.4f),
    //	CallFunc::create(CC_CALLBACK_0(CrashTest::removeThis, this)),
    //	nullptr)
    //	);
}

void HNSpriteTest::removeThis() {
    //auto child = getChildByTag(kTagGrossini);
    //child->removeChild(child, true);

    getTestSuite()->enterNextTest();
}

std::string HNSpriteTest::subtitle() const {
    return "HNSprite Test";
}