/*
 * TestScene.cpp
 *
 *  Created on: 2014年11月12日
 *      Author: Administrator
 */

#include "TestScene.h"

USING_NS_CC;
using namespace cocos2d::ui;

TestScene::TestScene()
    :cocosui_path("ccs-res/cocosui/")
    ,_count(0) {
}

Scene* TestScene::createScene() {
    auto scene = Scene::create();
    auto layer = TestScene::create();
    scene->addChild(layer);
    return scene;
}

bool TestScene::init() {
    if (!Layer::init()) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Button *enterButton = createButton();
    this->addChild(enterButton);
//
    Text* text = createText();
    this->addChild(text);

    TextBMFont* bmFont = createTextBMFont();
    this->addChild(bmFont);

    //TextField *textField = createTextField();
    //this->addChild(textField);

    TextAtlas* textAtlas = createTextAtlas();
    this->addChild(textAtlas);

    RichText* richText = createRichText();
    this->addChild(richText);

//
    ImageView* imageView = createImageView();
    this->addChild(imageView);

    CheckBox* checkBox = createCheckBox();
    this->addChild(checkBox);

    Slider* slider = createSlider();
    this->addChild(slider);

    //
    LoadingBar* loadingPar = createLoadingBar();
    loadingPar->setTag(10);
    this->addChild(loadingPar);
    scheduleUpdate();
    //
    PageView* pageView = createPageView();
    this->addChild(pageView);
    //
    ScrollView* scrollView = createScrollView();
    this->addChild(scrollView);

    return true;
}

void TestScene::update(float delta) {
    _count++;
    if (_count > 100) {
        _count = 0;
    }
    LoadingBar* loadingBar = static_cast<LoadingBar*>(this->getChildByTag(10));
    loadingBar->setPercent(_count);
}

/////////////////////////////////////////////////////////////////////
//按钮
/////////////////////////////////////////////////////////////////////
//特殊需求
//1.按钮里显示 需要消耗的物品形象
//2.在按钮右下角显示 物品的个数
Button* TestScene::createButton() {
//普通按钮
    Button *button = Button::create(cocosui_path + "button.png",
                                    cocosui_path + "buttonHighlighted.png");
    button->setTouchEnabled(true);
    button->setColor(Color3B::GREEN);
    button->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 2));
    button->loadTextures(cocosui_path + "button.png",
                         cocosui_path + "buttonHighlighted.png", "");

//九宫格按钮
//设置为九宫格按钮
    button->setScale9Enabled(true);
    button->setContentSize(Size(150, 70));

//add Pressed Action:点击放大效果
    button->setPressedActionEnabled(true);

//add button title
    button->setTitleText("Title Button");
    button->setTitleColor(Color3B::YELLOW);
    CCASSERT(button->getTitleColor() == Color3B::YELLOW, "Button setTitleColotr & getTitleColor not match!");

    button->addTouchEventListener(
        CC_CALLBACK_2(TestScene::handleButtonEvent, this));
    return button;
}

void TestScene::handleButtonEvent(cocos2d::Ref *pSender,
                                  cocos2d::ui::Widget::TouchEventType type) {
//只能使用Widget开头
    switch (type) {
    case Widget::TouchEventType::BEGAN: //按钮按下

        break;

    case Widget::TouchEventType::MOVED: //手指在按下和松起中间的移动

        break;

    case Widget::TouchEventType::ENDED: //手指正常松起
//		Director::getInstance()->end();
        break;

    case Widget::TouchEventType::CANCELED: //这个相对比较复杂点，指的是按下按钮，中间移动手指，把手指移到按钮边界外面，这样就被认定为取消操作

        break;

    default:
        break;
    }

}
/////////////////////////////////////////////////////////////////////
//单选框
/////////////////////////////////////////////////////////////////////
CheckBox* TestScene::createCheckBox() {
    CheckBox* checkBox = CheckBox::create(cocosui_path + "check_box_normal.png",
                                          cocosui_path + "check_box_normal_press.png",
                                          cocosui_path + "check_box_active.png",
                                          cocosui_path + "check_box_normal_disable.png",
                                          cocosui_path + "check_box_active_disable.png");

    checkBox->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 2));
    checkBox->addEventListener(
        CC_CALLBACK_2(TestScene::handleCheckBoxEvent, this));
    return checkBox;
}

void TestScene::handleCheckBoxEvent(cocos2d::Ref *pSender,
                                    cocos2d::ui::CheckBox::EventType type) {
    switch (type) {
    case CheckBox::EventType::SELECTED:
        break;

    case CheckBox::EventType::UNSELECTED:
        break;

    default:
        break;
    }
}

/////////////////////////////////////////////////////////////////////
//文本
/////////////////////////////////////////////////////////////////////

Text* TestScene::createText() {
    Text* alert = Text::create("CheckBox", "fonts/Marker Felt.ttf", 30);
    alert->setColor(Color3B(159, 168, 176));
    alert->setPosition(
        Vec2(visibleSize.width / 2.0f,
             visibleSize.height / 2.0f
             - alert->getContentSize().height * 1.75f));
    return alert;
}

TextAtlas* TestScene::createTextAtlas() {
    TextAtlas* textAtlas = TextAtlas::create("20141112",
                           cocosui_path + "labelatlas.png", 17, 22, "0");
    textAtlas->setPosition(
        Vec2((visibleSize.width) / 2.0f, visibleSize.height / 2.0f));
    return textAtlas;
}

TextBMFont* TestScene::createTextBMFont() {
    TextBMFont *text = TextBMFont::create("BMFont",
                                          cocosui_path + "bitmapFontTest2.fnt");
    text->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 2));
    text->setColor(Color3B::YELLOW);
    text->setOpacity(50);
    text->setName("text");
    return text;
}

TextField* TestScene::createTextField() {
//PlaceHolder是占位的意思，也就是用户未做任何输入时，文本框里显示的内容。
    //TextField *text = TextField::create("请输入密码", "_sans", 20);
    //text->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    //text->setColor(Color3B::GRAY); //设置文本颜色
    //text->setBright(true);
    //text->setBrightStyle(BrightStyle::HIGHLIGHT);
    //text->setTouchSize(Size(150, 50));
    //text->addEventListener(
    //	CC_CALLBACK_2(TestScene::handleTextFieldEvent, this));

    //ImageView* imageView = ImageView::create("CloseNormal.png",
    //	TextureResType::LOCAL);
    //text->addChild(imageView);
    //return text;
    return nullptr;
}

void TestScene::handleTextFieldEvent(cocos2d::Ref *pSender,
                                     cocos2d::ui::TextField::EventType type) {

    switch (type) {
    case TextField::EventType::ATTACH_WITH_IME: //虚拟键盘开启时

        break;

    case TextField::EventType::DETACH_WITH_IME: //虚拟键盘关闭时

        break;

    case TextField::EventType::INSERT_TEXT: //用户有输入文本时

        break;

    case TextField::EventType::DELETE_BACKWARD: //用户删除文本时

        break;

    default:
        break;
    }
}

RichText* TestScene::createRichText() {
    RichText* _richText = RichText::create();
//	是否忽略文本内容适配
    _richText->ignoreContentAdaptWithSize(false);
    _richText->setContentSize(Size(100, 100));

    RichElementText* re1 = RichElementText::create(1, Color3B::WHITE, 255,
                           "中国中国中国中国中国中国中国中国中国中国", "Marker Felt", 10);

    RichElementText* re2 = RichElementText::create(2, Color3B::YELLOW, 255,
                           "And this is yellow. ", "Helvetica", 10);

    RichElementText* re3 = RichElementText::create(3, Color3B::BLUE, 255,
                           "ご静聴ありがとうございました！！ご静聴ありがとうございました！！", "Helvetica", 10);

    RichElementText* re4 = RichElementText::create(4, Color3B::GREEN, 255,
                           "And green. ", "Helvetica", 10);

    RichElementText* re5 = RichElementText::create(5, Color3B::RED, 255,
                           "Last one is red ", "Helvetica", 10);

    RichElementImage* reimg = RichElementImage::create(6, Color3B::WHITE, 255,
                              cocosui_path + "sliderballnormal.png");

    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo(
        cocosui_path + "100/100.ExportJson");
    cocostudio::Armature *pAr = cocostudio::Armature::create("100");
    pAr->getAnimation()->play("Animation1");

    RichElementCustomNode* recustom = RichElementCustomNode::create(1,
                                      Color3B::WHITE, 255, pAr);

    RichElementText* re6 = RichElementText::create(7, Color3B::ORANGE, 255,
                           "Have fun!! ", "Helvetica", 10);

    _richText->pushBackElement(re1);
    _richText->insertElement(re2, 1);
    _richText->pushBackElement(re3);
    _richText->pushBackElement(re4);
    _richText->pushBackElement(re5);
    _richText->insertElement(reimg, 2);
    _richText->pushBackElement(recustom);
    _richText->pushBackElement(re6);

    _richText->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    _richText->setLocalZOrder(10);

    return _richText;
}

/////////////////////////////////////////////////////////////////////
//图片
/////////////////////////////////////////////////////////////////////
ImageView* TestScene::createImageView() {
    ImageView* imageView = ImageView::create(cocosui_path + "ccicon.png",
                           TextureResType::LOCAL);
    imageView->setVisible(true);
    imageView->loadTexture(cocosui_path + "ccicon.png");
    imageView->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    imageView->runAction(
        Sequence::create(FadeIn::create(0.5), DelayTime::create(1.0),
                         FadeOut::create(0.5), nullptr));

//	BlendFunc
//	Sprite
    return imageView;
}

/////////////////////////////////////////////////////////////////////
//滑动条
/////////////////////////////////////////////////////////////////////
Slider* TestScene::createSlider() {
    Slider* slider = Slider::create();
    slider->loadBarTexture(cocosui_path + "sliderTrack.png");
    slider->loadSlidBallTextures(cocosui_path + "sliderThumb.png",
                                 cocosui_path + "sliderThumb.png", "");
    slider->loadProgressBarTexture(cocosui_path + "sliderProgress.png");
    slider->setPosition(
        Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
    slider->addEventListener(CC_CALLBACK_2(TestScene::handleSliderEvent, this));
    return slider;
}

void TestScene::handleSliderEvent(cocos2d::Ref *pSender,
                                  cocos2d::ui::Slider::EventType type) {
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(pSender);

        int percent = slider->getPercent();

//		_displayValueLabel->setString(
//				String::createWithFormat("Percent %d", percent)->getCString());
    }
}

/////////////////////////////////////////////////////////////////////
//进度条
/////////////////////////////////////////////////////////////////////
LoadingBar* TestScene::createLoadingBar() {
    LoadingBar* loadingBar = LoadingBar::create(
                                 cocosui_path + "slider_bar_active_9patch.png");
    loadingBar->setTag(0);
    loadingBar->setScale9Enabled(true);
    loadingBar->setCapInsets(Rect(0, 0, 0, 0));
    loadingBar->setContentSize(Size(300, 13));
    loadingBar->setDirection(LoadingBar::Direction::RIGHT);

    loadingBar->setPosition(
        Vec2(visibleSize.width / 2.0f,
             visibleSize.height / 2.0f
             + loadingBar->getContentSize().height / 4.0f));

    return loadingBar;
}

/////////////////////////////////////////////////////////////////////
//滑动面板
/////////////////////////////////////////////////////////////////////

PageView* TestScene::createPageView() {
    PageView* pageView = PageView::create();
    pageView->setContentSize(Size(240.0f, 130.0f));

    Size backgroundSize = Size(642, 350);

    pageView->setPosition(
        Vec2(
            (visibleSize.width - backgroundSize.width) / 2.0f
            + (backgroundSize.width
               - pageView->getContentSize().width) / 2.0f,
            (visibleSize.height - backgroundSize.height) / 2.0f
            + (backgroundSize.height
               - pageView->getContentSize().height)
            / 2.0f));

    pageView->removeAllPages();

    int pageCount = 4;
    for (int i = 0; i < pageCount; ++i) {
        HBox* outerBox = HBox::create();
        outerBox->setContentSize(Size(240.0f, 130.0f));

        for (int k = 0; k < 2; ++k) {
            VBox* innerBox = VBox::create();

            for (int j = 0; j < 3; j++) {
                Button* btn = Button::create(
                                  cocosui_path + "animationbuttonnormal.png",
                                  cocosui_path + "animationbuttonpressed.png");
                btn->setName(StringUtils::format("button %d", j));
//				btn->addTouchEventListener(
//						CC_CALLBACK_2(TestScene::onButtonClicked, this));
//				btn->addTouchEventListener(this,
//						CC_CALLBACK_2(TestScene::onButtonClicked, this));

                innerBox->addChild(btn);
            }

            LinearLayoutParameter *parameter = LinearLayoutParameter::create();
            parameter->setMargin(Margin(0, 0, 100, 0));
            innerBox->setLayoutParameter(parameter);

            outerBox->addChild(innerBox);
        }

        pageView->insertPage(outerBox, i);
    }

    pageView->removePageAtIndex(0);

    //pageView->addEventListener(CC_CALLBACK_2(TestScene::handlePageViewEvent, this));

    return pageView;
}

ScrollView* TestScene::createScrollView() {
    ScrollView* scrollView = ScrollView::create();
    scrollView->setDirection(ScrollView::Direction::BOTH);
    scrollView->setTouchEnabled(true);
    scrollView->setBounceEnabled(true);
    scrollView->setBackGroundImageScale9Enabled(true);
    scrollView->setBackGroundImage(cocosui_path + "green_edit.png");
    scrollView->setContentSize(Size(210, 122.5));
    Size backgroundSize = Size(562, 327);
    scrollView->setPosition(
        Vec2(
            (visibleSize.width - backgroundSize.width) / 2.0f
            + (backgroundSize.width
               - scrollView->getContentSize().width)
            / 2.0f,
            (visibleSize.height - backgroundSize.height) / 2.0f
            + (backgroundSize.height
               - scrollView->getContentSize().height)
            / 2.0f));
    ImageView* imageView = ImageView::create("Hello.png");
    scrollView->addChild(imageView);

    scrollView->setInnerContainerSize(imageView->getContentSize());

    Size innerSize = scrollView->getInnerContainerSize();
    imageView->setPosition(
        Vec2(innerSize.width / 2.0f, innerSize.height / 2.0f));

    return scrollView;
}

void TestScene::handlePageViewEvent(cocos2d::Ref *pSender,
                                    cocos2d::ui::PageView::EventType type) {
    switch (type) {
    case PageView::EventType::TURNING: {
        PageView* pageView = dynamic_cast<PageView*>(pSender);

//		pageView->getCurPageIndex()
//		_displayValueLabel->setString(
//				CCString::createWithFormat("page = %ld",
//						pageView->getCurPageIndex() + 1)->getCString());
    }
    break;

    default:
        break;
    }
}

void TestScene::onButtonClicked(cocos2d::Ref *pSender,
                                cocos2d::ui::TouchEventType type) {

}
