#ifndef _PVR_TEST_H_
#define _PVR_TEST_H_

#include "framework\BaseTest.h"

DEFINE_TEST_SUITE(PVRTests);

class BasePVRTest : public TestCase {
public:
    BasePVRTest();
    ~BasePVRTest();
    CREATE_FUNC(BasePVRTest);

public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif ///_PVR_TEST_H_