#ifndef __H_TESTCASE_H__
#define __H_TESTCASE_H__

#include "ui/base/HNLayer.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC;
using namespace extension;
using namespace HN;

#define WinSize Director::getInstance()->getWinSize()

#define HEAD_CIRCLE "test/head-portrait4.png"
#define HEAD_STENCIL "test/head-portrait3.png"

namespace HN {
class TestCase : public HNLayer {

public:
    TestCase();
    ~TestCase();
    void testSpine();
    void testPlaySound();
    CREATE_FUNC(TestCase);

public:
    virtual bool init() override;

private:
    void testACheckBox();
    void testOpenURL();
    void testCSB();
    void testATableView();
    void testBTableView();
    void testButton();
    void testASlider();

    void sliderCallback(Ref *pSender, Control::EventType type);
    void testClipSprite();
    void testGBK2UTF8();
    void testHNSprite();
    void testDropdownList();
    void handleDropdownList(Ref *pSender, Control::EventType event);
    void testLabel();
    void testEffect();
    void checkTexture(float dt);
    Label *label;

private:
    void touchUp(Ref *pSender, Control::EventType type);
    void touchEffect(Ref *pSender, Widget::TouchEventType type);
    ccColor4B getPixelColor(unsigned char *data, const Vec2 &pos, Size size);
    unsigned char *getImageData(const char *filename);
};
}
#endif //__H_TESTCASE_H__
