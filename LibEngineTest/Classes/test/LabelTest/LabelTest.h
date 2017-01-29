#ifndef _LABEL_TEST_H_
#define _LABEL_TEST_H_

#include "framework\BaseTest.h"

DEFINE_TEST_SUITE(LabelTests);

class BaseLabelTest : public TestCase {
public:
    BaseLabelTest();
    ~BaseLabelTest();
    CREATE_FUNC(BaseLabelTest);

public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

public:
    void testGBK2UTF8();
};

#endif ///_LABEL_TEST_H_