#ifndef  _SLIDER_TEST_H_
#define  _SLIDER_TEST_H_

#include "framework/BaseTest.h"
#include "ui\base\ASlider.h"

DEFINE_TEST_SUITE(SliderTests);

class BaseSliderTest : public TestCase {
public:
    BaseSliderTest();
    ~BaseSliderTest();
    CREATE_FUNC(BaseSliderTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};


class ASliderTest : public TestCase {
public:
    CREATE_FUNC(ASliderTest);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;

    void removeThis();
public:
    void sliderCallback(Ref *pSender, Control::EventType type);
};

#endif ///_SLIDER_TEST_H_