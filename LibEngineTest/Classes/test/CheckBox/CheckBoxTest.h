#ifndef  _CHECKBOX_TEST_H_
#define  _CHECKBOX_TEST_H_

#include "framework/BaseTest.h"
#include "ui\base\ASlider.h"

DEFINE_TEST_SUITE(CheckBoxTests);

class BaseCheckBoxTest : public TestCase {
public:
    BaseCheckBoxTest();
    ~BaseCheckBoxTest();
    CREATE_FUNC(BaseCheckBoxTest);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};


class ACheckBoxTest : public TestCase {
public:
    CREATE_FUNC(ACheckBoxTest);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void removeThis();
};

#endif ///_CHECKBOX_TEST_H_