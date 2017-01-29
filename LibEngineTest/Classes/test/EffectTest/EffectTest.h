#ifndef _EFFECT_TEST_H_
#define _EFFECT_TEST_H_

#include "framework\BaseTest.h"
#include "ui/CocosGUI.h"

DEFINE_TEST_SUITE(EffectTests);

class BaseEffectTest : public TestCase {
public:
    BaseEffectTest();
    ~BaseEffectTest();
    CREATE_FUNC(BaseEffectTest);

public:
    virtual void onEnter() override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
public:
    void touchEffect(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
};

#endif ///_EFFECT_TEST_H_