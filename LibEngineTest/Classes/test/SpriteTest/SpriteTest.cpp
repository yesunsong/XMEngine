#include "SpriteTest.h"
#include "ui\extensions\ClipSprite.h"
#include "framework\testResource.h"
#include "globel\ApplicationMacro.h"
#include "test\HNLog.h"
#include "ui\base\AUIButton.h"
#include "utils\Tools.h"

enum {
    kTagBaseTest,
    kTagClipSprite,
};

SpriteTests::SpriteTests() {
    ADD_TEST_CASE(HNSpriteTest);
    ADD_TEST_CASE(ClipSpriteTest);
    ADD_TEST_CASE(GetSpritePixle);
}


//------------------------------------------------------------------
//
// BaseSpriteTest
//
//------------------------------------------------------------------

BaseSpriteTest::BaseSpriteTest(void) {
}

BaseSpriteTest::~BaseSpriteTest(void) {
}

std::string BaseSpriteTest::title() const {
    return "BaseSprite Test";
}
std::string BaseSpriteTest::subtitle() const {
    return "No title";
}


//------------------------------------------------------------------
//
// HNSpriteTest
//
//------------------------------------------------------------------

void HNSpriteTest::onEnter() {
    TestCase::onEnter();

    Texture2D *texture =
        Director::getInstance()->getTextureCache()->addImage("common/head/1.png");
    HNLog::logInfo("no add rc:%d", texture->getReferenceCount());

    auto sprite = HNSprite::create("common/head/1.png");
    sprite->setPosition(Vec2(sprite->getContentSize().width / 2,
                             sprite->getContentSize().height / 2));
    addChild(sprite);
    HNLog::logInfo("add one rc:%d", texture->getReferenceCount());

    auto sprite1 = HNSprite::create("common/head/1.png");
    sprite1->setPosition(Vec2(sprite1->getContentSize().width / 2,
                              sprite1->getContentSize().height / 2));
    addChild(sprite1);
    HNLog::logInfo("add two rc:%d", texture->getReferenceCount());

    removeChild(sprite);
    removeChild(sprite1);

    HNLog::logInfo("remove rc:%d", texture->getReferenceCount());

    //  schedule(schedule_selector(TestCase::checkTexture), 0.5f,
    //  CC_REPEAT_FOREVER,
    //           0.0f);
    //   schudel
    log("%s", Director::getInstance()
        ->getTextureCache()
        ->getCachedTextureInfo()
        .c_str());
}

void HNSpriteTest::removeThis() {
    auto child = getChildByTag(kTagBaseTest);
    child->removeChild(child, true);

    getTestSuite()->enterNextTest();
}

std::string HNSpriteTest::subtitle() const {
    return "HNSprite Test";
}

//------------------------------------------------------------------
//
// ClipSpriteTest
//
//------------------------------------------------------------------

void ClipSpriteTest::onEnter() {
    TestCase::onEnter();

    ClipSprite *clip = ClipSprite::create(StringUtils::format(PLAYER_HEAD, 1).c_str(), HEAD_STENCIL);
    clip->setPosition(Vec2(WIN_SIZE.width / 2, WIN_SIZE.height / 2));
    clip->setInverted(false);
    clip->getMaskSprite()->setScale(0.97f);
    clip->setTag(kTagClipSprite);
    // clip->getContentSprite()->setScale(0.9f);
    addChild(clip);

    auto blackQueue = Sprite::create(HEAD_CIRCLE);
    // blackQueue->setScale(1.17f);
    clip->addChild(blackQueue);
}

void ClipSpriteTest::removeThis() {
    auto child = getChildByTag(kTagClipSprite);
    child->removeChild(child, true);
    getTestSuite()->enterNextTest();
}

std::string ClipSpriteTest::subtitle() const {
    return "ClipSprite Test";
}


//------------------------------------------------------------------
//
// GetSpritePixle
//
//------------------------------------------------------------------

void GetSpritePixle::onEnter() {
    TestCase::onEnter();

    std::string file = "test/sprite/xianduizi_1.png";
    auto testBtn = AUIButton::create(file, file, file);
    testBtn->ignoreContentAdaptWithSize(false);
    testBtn->setPosition(Vec2(200, 200));
    testBtn->addTouchEventListener(CC_CALLBACK_2(GetSpritePixle::touchEffect, this));
    addChild(testBtn);
}

//TODO 有时候获取data会异常
void GetSpritePixle::touchEffect(Ref *pSender, Widget::TouchEventType type) {
    Button *button = dynamic_cast<Button *>(pSender);
    Vec2 pt = button->getTouchEndPosition(); //要获取的点
    pt = button->convertToNodeSpace(pt);
    HNLog::logInfo("------x:%f,y:%f", pt.x, pt.y);

    Size size;
    Image *imageData = Tools::getImageData("test/sprite/xianduizi_1.png", size);
    Color4B color = Tools::getPixelColor(imageData->getData(), pt, size);
    HNLog::logInfo("r:%d,g:%d,b:%d,a:%d", color.r, color.g, color.b, color.a);
    //  //
    //  //一下是获取某个像素的透明值,以此类推可以回去r,g,b的值
    //  Image *myImage = new Image();
    //  myImage->initWithImageFile("test/xianduizi.png");
    //  unsigned char *data = myImage->getData(); //这里就是图片数据了
    //  //根据刚刚计算的相对坐标值，计算出触摸点代表了哪一个像素点
    //  //      然后再提取出该像素点的alpha值
    //  //注意：因为图片坐标（0，0）是在左上角，所以要和触摸点的Y转换一下，也就是“(myImage->getHeight()
    //  //      - (int)(ps.y) - 1)”
    //  //该data值是把二维数组展开成一个一维数组,因为每个像素值由RGBA组成,所以每隔4个char为一个RGBA,并且像素以横向排列
    //  int pa = 4 * ((myImage->getHeight() - (int)(pt.y) - 1) *
    //  myImage->getWidth() +
    //                (int)(pt.x)) +
    //           3;
    //  unsigned int ap = data[pa];
    //  HNLog::logInfo("------x:%d", ap);
}

void GetSpritePixle::removeThis() {
    auto child = getChildByTag(kTagClipSprite);
    child->removeChild(child, true);
    getTestSuite()->enterNextTest();
}

std::string GetSpritePixle::subtitle() const {
    return "Get Sprite Pixle Test";
}