#ifndef  _SPRITE_TEST_H_
#define  _SPRITE_TEST_H_

#include "framework/BaseTest.h"

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

#endif ///_SPRITE_TEST_H_