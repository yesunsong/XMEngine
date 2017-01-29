#include "EffectTest.h"
#include "globel/ApplicationMacro.h"
#include "framework/testResource.h"
#include "ui/base/AUIButton.h"
#include "ui/extensions/Effect.h"
#include "test/HNLog.h"
#include "utils/Tools.h"

USING_NS_CC;
using namespace HN;

EffectTests::EffectTests() {
    ADD_TEST_CASE(BaseEffectTest);
}

//------------------------------------------------------------------
//
// BaseEffectTest
//
//------------------------------------------------------------------

BaseEffectTest::BaseEffectTest(void) {
}

BaseEffectTest::~BaseEffectTest(void) {
}

void BaseEffectTest::onEnter() {
    TestCase::onEnter();

    auto testBtn = AUIButton::create();
    testBtn->ignoreContentAdaptWithSize(false);
    testBtn->setContentSize(Size(400, 400));
    testBtn->setPosition(Vec2(200, 200));
    testBtn->addTouchEventListener(CC_CALLBACK_2(BaseEffectTest::touchEffect, this));
    addChild(testBtn);
    //
    auto csbEffect = Effect::createWithCSB("common/animation/baijiale/baijiale.csb");
    csbEffect->play("piaofu", true);
    csbEffect->setPosition(testBtn->getContentSize() / 2);
    this->addChild(csbEffect);

    HNLog::logInfo("effect width:%f,height:%f", csbEffect->getContentSize().width, csbEffect->getContentSize().height);

    auto spineEffect = Effect::createWithSpine("test/girl/girl.json", "test/girl/girl.atlas");
    spineEffect->play("daxiong", true);
    spineEffect->setPosition(Vec2(WIN_SIZE.width / 2, 0));
    addChild(spineEffect);


    //TODO 粒子没有播放出来
    auto particleEffect = Effect::createWithParticle("test/girl/girl_particle.plist");
    particleEffect->setPosition(Vec2(csbEffect->getPositionX(), csbEffect->getPositionY()));
    addChild(particleEffect);
}

void BaseEffectTest::touchEffect(Ref *pSender, Widget::TouchEventType type) {
}

std::string BaseEffectTest::title() const {
    return "PVR Test";
}

std::string BaseEffectTest::subtitle() const {
    return "Base PVR title";
}