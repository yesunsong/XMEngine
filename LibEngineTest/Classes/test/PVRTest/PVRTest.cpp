#include "PVRTest.h"
#include "globel/ApplicationMacro.h"
#include "framework/testResource.h"

USING_NS_CC;

PVRTests::PVRTests() {
    ADD_TEST_CASE(BasePVRTest);
}

//------------------------------------------------------------------
//
// BasePVRTest
//
//------------------------------------------------------------------

BasePVRTest::BasePVRTest(void) {
}

BasePVRTest::~BasePVRTest(void) {
}


void BasePVRTest::onEnter() {
    TestCase::onEnter();
}

std::string BasePVRTest::title() const {
    return "PVR Test";
}
std::string BasePVRTest::subtitle() const {
    return "Base PVR title";
}