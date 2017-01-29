#ifndef _RotateMenu_TEST_H_
#define _RotateMenu_TEST_H_

#include "framework/BaseTest.h"

DEFINE_TEST_SUITE(RotateMenuTests);

class BaseRotateMenuTest : public TestCase {
public:
    BaseRotateMenuTest();
    ~BaseRotateMenuTest();
    CREATE_FUNC(BaseRotateMenuTest);

public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class RotateMenuOneTest : public TestCase {
public:
    RotateMenuOneTest();
    ~RotateMenuOneTest();
    CREATE_FUNC(RotateMenuOneTest);

public:
    virtual void onEnter() override;
    void menuItem1Callback(cocos2d::Ref* pSender);
    void menuItem2Callback(cocos2d::Ref* pSender);
    void menuItem3Callback(cocos2d::Ref* pSender);
    void menuItem4Callback(cocos2d::Ref* pSender);
    void menuItem5Callback(cocos2d::Ref* pSender);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif ///_RotateMenu_TEST_H_