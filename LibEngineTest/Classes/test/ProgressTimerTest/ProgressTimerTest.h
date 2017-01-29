#ifndef _PROGRESSTIMER_TEST_H_
#define _PROGRESSTIMER_TEST_H_

#include "framework\BaseTest.h"

DEFINE_TEST_SUITE(ProgressTimerTests);

class BaseProgressTimerTest : public TestCase {
public:
    BaseProgressTimerTest();
    ~BaseProgressTimerTest();
    CREATE_FUNC(BaseProgressTimerTest);

public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif ///_PROGRESSTIMER_TEST_H_