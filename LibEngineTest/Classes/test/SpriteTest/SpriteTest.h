#ifndef  _SPRITE_TEST_H_
#define  _SPRITE_TEST_H_

#include "framework/BaseTest.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;

DEFINE_TEST_SUITE(SpriteTests);

class BaseSpriteTest : public TestCase {
public:
    BaseSpriteTest();
    ~BaseSpriteTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};


class HNSpriteTest : public BaseSpriteTest {
public:
    CREATE_FUNC(HNSpriteTest);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void removeThis();
};

class ClipSpriteTest : public BaseSpriteTest {
public:
    CREATE_FUNC(ClipSpriteTest);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void removeThis();
};

class GetSpritePixle : public BaseSpriteTest {
public:
    CREATE_FUNC(GetSpritePixle);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void removeThis();

public:
    void touchEffect(Ref *pSender, Widget::TouchEventType type);
};

#endif ///_SPRITE_TEST_H_