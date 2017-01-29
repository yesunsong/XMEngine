#ifndef _COCOSSTUDIO_TEST_H_
#define _COCOSSTUDIO_TEST_H_

#include "framework\BaseTest.h"

DEFINE_TEST_SUITE(CocosStudioTests);

class BaseCocosStudioTest : public TestCase {
public:
    BaseCocosStudioTest();
    ~BaseCocosStudioTest();
    CREATE_FUNC(BaseCocosStudioTest);

public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif ///_COCOSSTUDIO_TEST_H_