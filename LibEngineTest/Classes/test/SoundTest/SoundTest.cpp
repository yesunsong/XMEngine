#include "SoundTest.h"
#include "audio\HNAudioEngine.h"

using namespace HN;

SoundTests::SoundTests() {
    ADD_TEST_CASE(BaseSoundTest);
}

//------------------------------------------------------------------
//
// BaseSoundTest
//
//------------------------------------------------------------------

BaseSoundTest::BaseSoundTest(void) {
}

BaseSoundTest::~BaseSoundTest(void) {
}


void BaseSoundTest::onEnter() {
    TestCase::onEnter();

    for (int i = 0; i < 150; i++) {
        HNAudioEngine::getInstance()->playEffect("test/music/NN/dropGold.mp3");
    }
}

std::string BaseSoundTest::title() const {
    return "Sound Test";
}
std::string BaseSoundTest::subtitle() const {
    return "Base Sound Test";
}