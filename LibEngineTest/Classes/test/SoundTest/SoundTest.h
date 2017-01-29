#ifndef _SOUND_TEST_H_
#define _SOUND_TEST_H_

#include "framework\BaseTest.h"

DEFINE_TEST_SUITE(SoundTests);

class BaseSoundTest : public TestCase {
public:
    BaseSoundTest();
    ~BaseSoundTest();
    CREATE_FUNC(BaseSoundTest);

public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif ///_SOUND_TEST_H_