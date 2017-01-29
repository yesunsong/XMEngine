#include "SliderTest.h"

#include "framework\testResource.h"

enum {
    kTagBaseSlider,
    kTagASlider,
};

SliderTests::SliderTests() {
    ADD_TEST_CASE(BaseSliderTest);
    ADD_TEST_CASE(ASliderTest);
}


//------------------------------------------------------------------
//
// BaseSliderTest
//
//------------------------------------------------------------------

BaseSliderTest::BaseSliderTest(void) {
}

BaseSliderTest::~BaseSliderTest(void) {
}

std::string BaseSliderTest::title() const {
    return "Base Slider Test";
}
std::string BaseSliderTest::subtitle() const {
    return "No title";
}


//------------------------------------------------------------------
//
// ASliderTest
//
//------------------------------------------------------------------

void ASliderTest::onEnter() {
    TestCase::onEnter();

    ASlider *slider =ASlider::create(BRNN_SET_SCROLL_BAR_BG, BRNN_SET_SCROLL_BAR_FOREBG,BRNN_SET_SCROLL_BAR_BALL);
    slider->setRotation(90);
    slider->setPosition(Vec2(slider->getContentSize().width / 2,slider->getContentSize().height + 200));
    slider->setMaximumValue(100);
    slider->setMinimumValue(0);
    slider->setValue(0);
    slider->setOffsetX(0);
    slider->setMaskDiff(15);
    slider->setProgressSpritePositionX(20);
    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(ASliderTest::sliderCallback),Control::EventType::VALUE_CHANGED);
    slider->setTag(kTagASlider);
    slider->setSliderEndedCallback([]() {
        log("touch up");
    });
    addChild(slider);
}

void ASliderTest::sliderCallback(Ref *pSender, Control::EventType type) {
    // log("xxx type:%s", type);
    ASlider *pSlider = static_cast<ASlider *>(pSender);
    if (pSlider->isSelected()) {
        // log("xxxx selected:%d", pSlider->isSelected());
        log("xxx slider:%f,%f", pSlider->getValue(), 0);
    }
}

void ASliderTest::removeThis() {
    auto child = getChildByTag(kTagASlider);
    child->removeChild(child, true);

    getTestSuite()->enterNextTest();
}

std::string ASliderTest::subtitle() const {
    return "ASlider Test";
}