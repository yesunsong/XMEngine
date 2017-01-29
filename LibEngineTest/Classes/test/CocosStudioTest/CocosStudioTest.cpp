#include "CocosStudioTest.h"
#include "cocostudio/CocoStudio.h"
#include "globel/ApplicationMacro.h"
#include "framework/testResource.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace cocostudio;

CocosStudioTests::CocosStudioTests() {
    ADD_TEST_CASE(BaseCocosStudioTest);
}

//------------------------------------------------------------------
//
// BaseCocosStudioTest
//
//------------------------------------------------------------------

BaseCocosStudioTest::BaseCocosStudioTest(void) {
}

BaseCocosStudioTest::~BaseCocosStudioTest(void) {
}


void BaseCocosStudioTest::onEnter() {
    TestCase::onEnter();

    auto loader = CSLoader::createNode("common/animation/heguan/heguan.csb");
    loader->setPosition(WIN_SIZE / 2);
    addChild(loader);

    auto loader2 = CSLoader::createNode(ANIMATION_VS_HIT_CSB);
    loader2->setPosition(Vec2(WIN_SIZE.width/2,WIN_SIZE.height/2) + Vec2(250.0f,250.0f));
    addChild(loader2);

    auto antAction = CSLoader::createTimeline(ANIMATION_VS_HIT_CSB);
    loader2->runAction(antAction);
    antAction->play("hit", true);
}

std::string BaseCocosStudioTest::title() const {
    return "Cocos Studio Test";
}
std::string BaseCocosStudioTest::subtitle() const {
    return "Base Cocos Studio Test";
}