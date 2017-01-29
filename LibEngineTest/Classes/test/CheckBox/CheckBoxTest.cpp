#include "CheckBoxTest.h"

#include "framework\testResource.h"
#include "ui\base\ACheckBox.h"
#include "globel\ApplicationMacro.h"
#include "test\HNLog.h"

enum {
    kTagBaseCheckBox,
    kTagACheckBox,
};

CheckBoxTests::CheckBoxTests() {
    ADD_TEST_CASE(BaseCheckBoxTest);
    ADD_TEST_CASE(ACheckBoxTest);
}


//------------------------------------------------------------------
//
// BaseCheckBoxTest
//
//------------------------------------------------------------------

BaseCheckBoxTest::BaseCheckBoxTest(void) {
}

BaseCheckBoxTest::~BaseCheckBoxTest(void) {
}

std::string BaseCheckBoxTest::title() const {
    return "Base CheckBox Test";
}
std::string BaseCheckBoxTest::subtitle() const {
    return "No title";
}


//------------------------------------------------------------------
//
// ACheckBoxTest
//
//------------------------------------------------------------------

void ACheckBoxTest::onEnter() {
    TestCase::onEnter();

    ACheckBox *checkBox = ACheckBox::create(TOOLBAR_NEXT_EXIT, TOOLBAR_CHECKBOX);
    checkBox->setPosition(WIN_SIZE / 2);
    checkBox->setSelected(true);
    checkBox->seBackGroundSelectedBox(Vec2(100, 200));
    checkBox->setTag(kTagACheckBox);
    addChild(checkBox);
    HNLog::logInfo("selected:&d", checkBox->isSelected());
}

void ACheckBoxTest::removeThis() {
    auto child = getChildByTag(kTagACheckBox);
    child->removeChild(child, true);

    getTestSuite()->enterNextTest();
}

std::string ACheckBoxTest::subtitle() const {
    return "ACheckBox Test";
}