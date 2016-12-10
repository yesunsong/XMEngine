//#include "stdafx.h"
#include "TestCase.h"
//#include "BRNNHelpLayer.h"
//#include "BRNNRes.h"
//#include "BRNNSettlementLayer.h"
#include "ui/base//ACheckBox.h"
#include "ui/base//AControlButton.h"
#include "ui/base//ASlider.h"
#include "ui/base//ATableView.h"
#include "ui/base//AUIButton.h"
#include "ui/base//BTableView.h"
#include "ui/base/HNSprite.h"
#include "ui/extensions/ClipSprite.h"
//#include "ui/extensions/DropdownList.h"
//#include "HNCommon/HNConverCode.h"
//#include "HNCommon/HNLog.h"
//#include "HNLobby/GamePrompt.h"
#include "ui/extensions/TextureLayer.h"
#include "cocostudio/CocoStudio.h"
#include "HNEngineExport.h"
// spine所需要的文件
#include "spine/spine.h"
#include <spine/spine-cocos2dx.h>
using namespace spine;
// end spine

TestCase::TestCase() {}

TestCase::~TestCase() {}

bool HN::TestCase::init() {
    if (!HNLayer::init()) {
        return false;
    }
    //  testHNSprite();
    // testASlider();
    //  testButton();
    // testATableView();
    // testBTableView();
    // testClipSprite();
    // testGBK2UTF8();
    testCSB();
    // testLabel();
    // testDropdownList();
    // testACheckBox();
    // testOpenURL();
    // testSpine();

    //  testEffect();

    // label = Label::createWithTTF("", DEFAULT_FONT, FONT_SIZE_25);
    // label->setPosition(WinSize / 2);
    // addChild(label);
    // testPlaySound();
    //
    // BRNN::BRNNSettlementLayer* test = BRNN::BRNNSettlementLayer::create();
    // test->setPosition(Vec2(WinSize.width/2,WinSize.height/2));
    // test->setBankerMoney("0123456");
    // test->setMyselfMoney("012");
    // addChild(test);

    //  Texture2D *texture =
    //      Director::getInstance()->getTextureCache()->addImage("star.png");
    //  cocos2d::Texture2D::PixelFormat format = texture->getPixelFormat();
    //  HNLog::logInfo("format:%d %s", format, texture->getDescription().c_str());
    //
    //  Texture2D *texture1 =
    //      Director::getInstance()->getTextureCache()->addImage("platform/0.png");
    //  cocos2d::Texture2D::PixelFormat format1 = texture1->getPixelFormat();
    //  HNLog::logInfo("format 1:%d %s", format1,
    //  texture1->getDescription().c_str());

    //  auto textureLayer = TextureLayer::create(.);
    //  addChild(textureLayer);

    //
    return true;
}

void TestCase::touchEffect(Ref *pSender, Widget::TouchEventType type) {
    HNLog::logInfo("touch");

    Button *button = dynamic_cast<Button *>(pSender);
    Vec2 pt = button->getTouchEndPosition(); //要获取的点

    pt = button->convertToNodeSpace(pt);

    HNLog::logInfo("------x:%f,y:%f", pt.x, pt.y);

    Size size;
    Color4B c(0, 0, 0, 0);
    Image *data_ = Tools::getImageData("test/xianduizi.png", size);
    c = Tools::getPixelColor(data_->getData(), pt, size);
    HNLog::logInfo("r:%d,g:%d,b:%d,a:%d", c.r, c.g, c.b, c.a);
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

unsigned char *TestCase::getImageData(const char *filename) {
    Image *myimg = new Image();
    myimg->initWithImageFile(filename);
    unsigned char *data_ = myimg->getData();
    delete myimg;
    return data_;
}

ccColor4B TestCase::getPixelColor(unsigned char *data, const Vec2 &pos,
                                  Size size) {
    unsigned int x = pos.x, y = pos.y, width = size.width, height = size.height;
    ccColor4B c = {0, 0, 0, 0};
    unsigned int *pixel = (unsigned int *)data;
    pixel = pixel + ((height - y - 1) * width + x);
    c.r = *pixel & 0xff;
    c.g = (*pixel >> 8) & 0xff;
    c.b = (*pixel >> 16) & 0xff;
    c.a = (*pixel >> 24) & 0xff; //这个值  就是透明度
    HNLog::logInfo("r:%d,g:%d,b:%d,a:%d", c.r, c.g, c.b, c.a);
    return c;
}

void TestCase::testEffect() {
    auto testBtn = AUIButton::create();
    testBtn->ignoreContentAdaptWithSize(false);
    testBtn->setContentSize(Size(400, 400));
    testBtn->setPosition(Vec2(200, 200));
    testBtn->addTouchEventListener(CC_CALLBACK_2(TestCase::touchEffect, this));
    addChild(testBtn);
    //
    auto effect = Effect::createWithCSB("common/animation/baijiale/baijiale.csb");
    effect->play("piaofu", true);
    effect->setPosition(testBtn->getContentSize() / 2);
    testBtn->addChild(effect);

    HNLog::logInfo("effect width:%f,height:%f", effect->getContentSize().width,
                   effect->getContentSize().height);

    auto effect1 =
        Effect::createWithSpine("test/girl/girl.json", "test/girl/girl.atlas");
    effect1->play("daxiong", true);
    effect1->setPosition(Vec2(WinSize.width / 2, 0));
    //  addChild(effect1);
    //  testBtn->addChild(effect1);

    auto effect2 = Effect::createWithParticle("test/girl/girl_particle.plist");
    effect2->setPosition(Vec2(
                             effect1->getPositionX() +
                             (effect1->getContentSize().width - effect2->getContentSize().width) /
                             2,
                             effect1->getPositionY()));
    addChild(effect2);
}

void TestCase::testSpine() {
    auto skeletonNode = SkeletonAnimation::createWithFile("test/girl/girl.json",
                        "test/girl/girl.atlas");
    skeletonNode->setPosition(Vec2(WinSize.width / 2, 0));

    skeletonNode->setAnimation(0, "daxiong", true);
    addChild(skeletonNode);
    //
    ParticleSystemQuad *particle =
        ParticleSystemQuad::create("test/girl/girl_particle.plist");
    particle->setPosition(Vec2(skeletonNode->getPositionX() +
                               (skeletonNode->getContentSize().width -
                                particle->getContentSize().width) /
                               2,
                               skeletonNode->getPositionY()));

    addChild(particle);
}

void TestCase::testPlaySound() {
    for (int i = 0; i < 150; i++) {
        HNAudioEngine::getInstance()->playEffect("music/NN/dropGold.mp3");
        label->setString(StringUtils::format("%d", i));
    }
}

void TestCase::testACheckBox() {
    ACheckBox *checkBox = ACheckBox::create(TOOLBAR_NEXT_EXIT, TOOLBAR_CHECKBOX);
    checkBox->setPosition(WIN_SIZE / 2);
    addChild(checkBox);
    checkBox->setSelected(true);
    checkBox->seBackGroundSelectedBox(Vec2(100, 200));

    HNLog::logInfo("selected:&d", checkBox->isSelected());
}

// Android和iOS自带支持打开本地浏览器
void TestCase::testOpenURL() {
    Application::getInstance()->openURL(
        "http://client-10059516.file.myqcloud.com/game8090.apk");
}

void TestCase::testDropdownList() {
    auto dropdownList = DropdownList::create();
    dropdownList->setPosition(WIN_SIZE / 2);
    dropdownList->setSetBtnCallback(
        cccontrol_selector(TestCase::handleDropdownList));
    dropdownList->setLeaveBtnCallback(
        cccontrol_selector(TestCase::handleDropdownList));
    dropdownList->setNextRoundBtnCallback(
        cccontrol_selector(TestCase::handleDropdownList));
    dropdownList->setHelpBtnCallback(
        cccontrol_selector(TestCase::handleDropdownList));
    addChild(dropdownList);
}

//注意回调函数的this指向
void TestCase::handleDropdownList(Ref *pSender, Control::EventType event) {
    Node *btn = (Node *)pSender;
    switch (btn->getTag()) {
    case DropdownListTag::DL_SetBtn: {
        HNLog::logInfo("点击了设置按钮");
    }
    break;
    case DropdownListTag::DL_HelpBtn: {
        HNLog::logInfo("点击了帮助按钮");
        auto helpLayer = BRNN::BRNNHelpLayer::create();
        helpLayer->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2));
        btn->getParent()->getParent()->addChild(helpLayer);
        // this指向的是dropdownList，所以不能使用以下方法
        // this->addChild(helpLayer);
    }
    break;
    case DropdownListTag::DL_LeaveBtn: {
        HNLog::logInfo("点击了离开按钮");
    }
    break;
    case DropdownListTag::DL_NextRoundExitBtn: {
        HNLog::logInfo("点击了下一轮退出按钮");
        (dynamic_cast<DropdownList *>(btn->getParent()))->changeCheckBox();
    }
    break;
    }
}

void TestCase::testLabel() {
    auto bankerMoneyLabel =
        LabelAtlas::create(":;123456789", FNT_YELLOW_THREE, 22, 28, '0');
    bankerMoneyLabel->setPosition(WIN_SIZE.width / 2, WIN_SIZE.height / 2);
    addChild(bankerMoneyLabel);

    auto myMoneyLabel =
        LabelAtlas::create(":;123456789", FNT_BLUE_ONE, 22, 28, '0');
    myMoneyLabel->setPosition(bankerMoneyLabel->getPositionX(),
                              bankerMoneyLabel->getPositionY() -
                              bankerMoneyLabel->getContentSize().height);
    addChild(myMoneyLabel);
}

void TestCase::testCSB() {
    auto loader = CSLoader::createNode("common/animation/heguan/heguan.csb");
    loader->setPosition(Vec2((WinSize.width) / 2, (WinSize.height) / 2));
    addChild(loader);
    //
    //  dynamic_cast<TextBMFont *>(loader->getChildByTag(7))->setString("012");
    //  dynamic_cast<TextBMFont *>(loader->getChildByTag(8))->setString("-012");
    //  HNLog::logDebug("content size:%f-%f", loader->getContentSize().width,
    //                  loader->getContentSize().height);

    auto loader2 = CSLoader::createNode("test/shisanzhang/MainScene.csb");
    addChild(loader2);

    auto antAction = CSLoader::createTimeline("test/shisanzhang/MainScene.csb");
    loader2->runAction(antAction);

    antAction->play("shisanzhang", true);
}

void TestCase::testGBK2UTF8() {
    auto label = Label::create("", "Arial", 24);
    label->setPosition(Vec2(WinSize.width / 2, WinSize.height / 2));
    addChild(label);
    label->setString(GBKToUtf8("中国人"));
    //
    // XMLParser* parser = XMLParser::parseWithFile("config/strings.xml");
    // string name=parser->getString("app_name");
    label->setString(
        GetText("tuoguan_tips")); // TODO tuoguan_tips这个为什么没有显示出来

    auto label1 = Label::create("", "Arial", 24);
    label1->setPosition(Vec2(WinSize.width / 2, WinSize.height / 2 - 100));
    addChild(label1);
    label1->setString(StringUtils::format(
                          GetText("union_banker"), 1)); // TODO tuoguan_tips这个为什么没有显示出来
}

void TestCase::testHNSprite() {
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

void TestCase::checkTexture(float dt) {
    log("%s", Director::getInstance()
        ->getTextureCache()
        ->getCachedTextureInfo()
        .c_str());
}

void TestCase::testATableView() {
    CreateTableCellCallback callback = [&](TableView *table,
    ssize_t idx) -> TableViewCell * {
        TableViewCell *Cell = table->dequeueCell();
        if (!Cell) {
            Cell = new TableViewCell();
            Cell->autorelease();
        }
        Cell->removeAllChildrenWithCleanup(false);
        //获取size的大小
        Size size = (dynamic_cast<ATableView *>(table))->cellSizeForTable(table);
        return Cell;
    };

    ATableView *tableView = ATableView::create(callback);
    tableView->setViewSize(WinSize);
    tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    tableView->setPosition(Vec2(200, 200));
    tableView->setNumberOfCellsInTableView(10);
    tableView->reloadData();
    addChild(tableView);
}

void TestCase::testBTableView() {
    BTableView *m_pTableView = BTableView::createWithSlider(
                                   BRNN_SET_SCROLL_BAR_BG, BRNN_SET_SCROLL_BAR_FOREBG,
                                   BRNN_SET_SCROLL_BAR_BALL,
    [](TableView *table, ssize_t idx) -> TableViewCell * {
        TableViewCell *Cell = table->dequeueCell();
        if (!Cell) {
            Cell = new TableViewCell();
            Cell->autorelease();
        }
        Cell->removeAllChildrenWithCleanup(true);
        //获取size的大小
        Size size =
        (dynamic_cast<ATableView *>(table))->cellSizeForTable(table);

        auto name = Label::create(
            GBKToUtf8(StringUtils::format("中国人-%d", idx).c_str()), "", 25);
        name->setColor(Color3B::RED);
        name->setPosition((size.width / 2), (size.height / 2));
        Cell->addChild(name);
        return Cell;
    });
    m_pTableView->setDirection(
        cocos2d::extension::ScrollView::Direction::VERTICAL);

    // BTW:这几个顺序不能反过来
    // setDirection
    // setPosition
    // setViewSize
    // reloadData
    int num = 5;
    float cellWidth = 120;
    float cellHeight = 120;
    float viewWidth = cellWidth * num;
    float viewHeight = cellHeight * num;

    if (m_pTableView->getTable()->isVertical()) {
        m_pTableView->setPosition(0, 100);
        m_pTableView->setViewSize(Size(viewWidth, viewHeight));
        m_pTableView->setTableCellSize(Size(viewWidth, cellHeight));
    } else if (m_pTableView->getTable()->isHorizontal()) {
        m_pTableView->setPosition(100, 200);
        m_pTableView->setViewSize(Size(viewWidth, 50));
        m_pTableView->setTableCellSize(Size(cellWidth, 50));
    }
    m_pTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    m_pTableView->setProgressOpacity(0);
    m_pTableView->setNumberOfCellsInTableView(10);
    m_pTableView->reloadData();
    m_pTableView->getSlider()->setValue(0.0f);
    this->addChild(m_pTableView);
}

void TestCase::testButton() {
    //第一种写法
    // auto testBtn = AButton::create();
    // testBtn->loadTextures(BRNN_TABLERES_BTN_MAKER1, BRNN_TABLERES_BTN_MAKER1,
    // BRNN_TABLERES_BTN_MAKER1);
    //第二种写法
    string bg = "common/button1/5.png";
    string title = "common/button1/17.png";
    auto testBtn = AUIButton::create(bg, bg, bg);
    testBtn->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    testBtn->setPosition(Vec2(300, 300));
    testBtn->setPressedActionEnabled(true);
    testBtn->setTitle(title);
    testBtn->setGray(true);
    testBtn->setEnabled(true);
    // addChild(testBtn);
    //////////////////////////////////////////////////////////////////////////
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(bg);
    auto testBtn1 = AControlButton::create(bg.c_str());
    testBtn1->setPosition(Vec2(300, 600));
    testBtn1->setPreferredSize(texture->getContentSize());
    testBtn1->setTitle(title.c_str());
    testBtn1->setGray(true);
    testBtn1->setHighlighted(true);
    // addChild(testBtn1);
    //
    auto testBtn2 = Button::create("test/xianduizi.png");
    testBtn2->setPosition(Vec2(300, 200));
    testBtn2->setPressedActionEnabled(true);
    testBtn2->addTouchEventListener(CC_CALLBACK_2(TestCase::touchEffect, this));
    addChild(testBtn2);
}

void TestCase::testASlider() {
    ASlider *slider =
        ASlider::create(BRNN_SET_SCROLL_BAR_BG, BRNN_SET_SCROLL_BAR_FOREBG,
                        BRNN_SET_SCROLL_BAR_BALL);
    slider->setRotation(90);
    slider->setPosition(Vec2(slider->getContentSize().width / 2,
                             slider->getContentSize().height + 200));
    slider->setMaximumValue(100);
    slider->setMinimumValue(0);
    slider->setValue(0);
    slider->setOffsetX(0);
    slider->setMaskDiff(15);
    slider->setProgressSpritePositionX(20);
    slider->addTargetWithActionForControlEvents(
        this, cccontrol_selector(TestCase::sliderCallback),
        Control::EventType::VALUE_CHANGED);
    slider->setSliderEndedCallback([]() {
        log("touch up");
    });
    addChild(slider);
}

void TestCase::sliderCallback(Ref *pSender, Control::EventType type) {
    // log("xxx type:%s", type);
    ASlider *pSlider = static_cast<ASlider *>(pSender);
    if (pSlider->isSelected()) {
        // log("xxxx selected:%d", pSlider->isSelected());
        log("xxx slider:%f,%f", pSlider->getValue(), 0);
    }
}

void TestCase::testClipSprite() {
    auto blackQueue = Sprite::create(HEAD_CIRCLE);
    // blackQueue->setScale(1.17f);

    ClipSprite *clip = ClipSprite::create(
                           StringUtils::format(PLAYER_HEAD, 1).c_str(), HEAD_STENCIL);
    clip->setPosition(Vec2(WinSize.width / 2, WinSize.height / 2));
    clip->setInverted(false);
    clip->getMaskSprite()->setScale(0.97f);
    // clip->getContentSprite()->setScale(0.9f);
    addChild(clip);

    clip->addChild(blackQueue);
}
