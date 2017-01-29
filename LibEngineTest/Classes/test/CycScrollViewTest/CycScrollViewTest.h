#ifndef _CYSCROLLVIEW_TEST_H_
#define _CYSCROLLVIEW_TEST_H_

#include "framework/BaseTest.h"

DEFINE_TEST_SUITE(CycScrollViewTests);

class BaseCycScrollViewTest : public TestCase {
public:
    BaseCycScrollViewTest();
    ~BaseCycScrollViewTest();
    CREATE_FUNC(BaseCycScrollViewTest);

public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif ///_CYSCROLLVIEW_TEST_H_