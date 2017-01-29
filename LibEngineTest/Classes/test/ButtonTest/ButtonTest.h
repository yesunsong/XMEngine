#ifndef _BUTTON_TEST_H_
#define _BUTTON_TEST_H_

#include "framework\BaseTest.h"

DEFINE_TEST_SUITE(ButtonTests);

class BaseButtonTest : public TestCase {
public:
    BaseButtonTest();
    ~BaseButtonTest();
    CREATE_FUNC(BaseButtonTest);

public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif ///_BUTTON_TEST_H_