#ifndef _APPLICATION_TEST_H_
#define _APPLICATION_TEST_H_

#include "framework\BaseTest.h"

DEFINE_TEST_SUITE(ApplicationTests);

class BaseApplicationTest : public TestCase {
public:
    BaseApplicationTest();
    ~BaseApplicationTest();
    CREATE_FUNC(BaseApplicationTest);

public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif ///_APPLICATION_TEST_H_