/*
 * TestScene.h
 *
 *  Created on: 2014年11月12日
 *      Author: Administrator
 */

#ifndef TESTSCENE_H_
#define TESTSCENE_H_

#include <stdio.h>;
#include <string.h>;
#include "cocos2d.h";
#include "cocostudio/CocoStudio.h";
#include "ui/CocosGUI.h"

class TestScene: public cocos2d::Layer {
public:
    TestScene();

    static cocos2d::Scene* createScene();

    virtual bool init();

    cocos2d::ui::Text* createText();
    cocos2d::ui::TextAtlas* createTextAtlas();
    cocos2d::ui::TextField* createTextField();
    cocos2d::ui::TextBMFont* createTextBMFont();
    cocos2d::ui::RichText* createRichText();

    cocos2d::ui::Button* createButton();

    cocos2d::ui::ImageView* createImageView();

    cocos2d::ui::CheckBox* createCheckBox();

    cocos2d::ui::Slider* createSlider();

    cocos2d::ui::LoadingBar* createLoadingBar();

    cocos2d::ui::PageView* createPageView();

    cocos2d::ui::ScrollView* createScrollView();

    void handleButtonEvent(cocos2d::Ref *pSender,
                           cocos2d::ui::Widget::TouchEventType type);

    void handleTextFieldEvent(cocos2d::Ref *pSender,
                              cocos2d::ui::TextField::EventType type);

    void handleCheckBoxEvent(cocos2d::Ref *pSender,
                             cocos2d::ui::CheckBox::EventType type);

    void handleSliderEvent(cocos2d::Ref *pSender,
                           cocos2d::ui::Slider::EventType type);

    void update(float delta);

    void handlePageViewEvent(cocos2d::Ref *pSender,
                             cocos2d::ui::PageView::EventType type);

    void onButtonClicked(cocos2d::Ref *pSender,
                         cocos2d::ui::TouchEventType type);
    //

    CREATE_FUNC(TestScene)
    ;
private:
    int _count;
    std::string cocosui_path = "";
    cocos2d::Size visibleSize;
}
;

#endif /* TESTSCENE_H_ */
