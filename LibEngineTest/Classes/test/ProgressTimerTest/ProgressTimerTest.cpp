#include "ProgressTimerTest.h"
#include "ui\extensions\MyProgressTimer.h"
#include "globel\ApplicationMacro.h"

ProgressTimerTests::ProgressTimerTests() {
    ADD_TEST_CASE(BaseProgressTimerTest);
}

//------------------------------------------------------------------
//
// BaseProgressTimerTest
//
//------------------------------------------------------------------

BaseProgressTimerTest::BaseProgressTimerTest(void) {
}

BaseProgressTimerTest::~BaseProgressTimerTest(void) {
}


void BaseProgressTimerTest::onEnter() {
    TestCase::onEnter();

    //auto timerSp = Sprite::create(PROGRESS_SRC);
    ProgressTimer* _progressTimer = ProgressTimer::create(Sprite::create("test/progresstimer/progressbar.png"));
    this->addChild(_progressTimer);
    //_progressTimer->setScaleX(WIN_SIZE.width / timerSp->getContentSize().width);
    //_progressTimer->setScaleY(size.height / timerSp->getContentSize().height);
    //_progressTimer->setPosition(WIN_SIZE/2);
    //_progressTimer->setPercentage(50.0f);
    //_progressTimer->setVisible(false);
    _progressTimer->setReverseProgress(true);
    //
    MyProgressTimer* progressTimer = MyProgressTimer::create(Sprite::create("test/progresstimer/progressbar.png"));
    progressTimer->setPosition(Vec2(WIN_SIZE.width / 2, WIN_SIZE.height*0.5));
    progressTimer->setOrigin(Vec2(0.12, 0.12));
    progressTimer->setTop(Vec2(0.88, 0.88));
    progressTimer->setForebackground(Sprite::create("test/progresstimer/progressbar2.png"));
    progressTimer->stopAllActions();
    progressTimer->runAction(Sequence::create(MyProgressFromTo::create(15.0f, 0, 100),
    CallFunc::create([&]() {
        CCLOG("CallFunc: end!");
    }), nullptr));
    //this->addChild(progressTimer);
}

std::string BaseProgressTimerTest::title() const {
    return "ProgressTimer Test";
}
std::string BaseProgressTimerTest::subtitle() const {
    return "Base ProgressTimer Test";
}