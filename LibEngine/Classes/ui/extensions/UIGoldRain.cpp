//#include "stdafx.h"
#include "UIGoldRain.h"
//#include "class_global_data.h"
#include "audio/HNAudioEngine.h"

class UICoin :public Sprite {
public:
    UICoin(void);
    ~UICoin(void);
    virtual bool init();
    CREATE_FUNC(UICoin);
    void Play();
};

UICoin::UICoin(void) {

}
UICoin::~UICoin(void) {

}

bool UICoin::init() {
    if (!CCSprite::init())
        return false;
    return true;
}

void UICoin::Play() {
    stopAllActions();
    Animation* ptr_animation_coin = Animation::create();
    int int_id = rand() % 7;

    char str[128] = { 0 };
    for (int i = int_id; i <= 7; i++) {
        //String* ptr_str_filaname = CCString::createWithFormat("common/gold_frame_%d.png", i);
        sprintf(str, "common/animation/goldFall/gold_frame_%d.png", i);
        SpriteFrame* ptr_frame = SpriteFrame::create(str, Rect(0, 0, 65, 65));
        ptr_animation_coin->addSpriteFrame(ptr_frame);
    }
    for (int i = 0; i < int_id; i++) {
        //CCString* ptr_str_filaname = CCString::createWithFormat("common/gold_frame_%d.png", i);
        sprintf(str, "common/animation/goldFall/gold_frame_%d.png", i);
        SpriteFrame* ptr_frame = SpriteFrame::create(str, Rect(0, 0, 65, 65));
        ptr_animation_coin->addSpriteFrame(ptr_frame);
    }
    ptr_animation_coin->setDelayPerUnit(0.7f / 7.0f);
    ptr_animation_coin->setRestoreOriginalFrame(true);
    ptr_animation_coin->setLoops(-1);
    Animate* ptr_animate_coin = CCAnimate::create(ptr_animation_coin);
    runAction(ptr_animate_coin);
}

///////////////////////////////////////

UIGoldRain* sptr_gold_rain = 0;

void UIGoldRain::ShowGoldRain(Scene* parent) {
    if (sptr_gold_rain == 0) {
        sptr_gold_rain = UIGoldRain::create();
        parent->addChild(sptr_gold_rain);
        sptr_gold_rain->setLocalZOrder(100000);
    }
    if (sptr_gold_rain)
        sptr_gold_rain->show_glod_rain();
}

UIGoldRain::UIGoldRain() {

}
UIGoldRain::~UIGoldRain() {
    sptr_gold_rain = 0;
}
bool UIGoldRain::init() {
    if (!Layout::init())
        return false;

    Director* ptr_director = Director::getInstance();
    Size the_director_size = ptr_director->getVisibleSize();

    setContentSize(the_director_size);
    setPosition(Vec2::ZERO);
    for (int i = 0; i < 80; i++) {
        UICoin *ptr_coin = UICoin::create();
        ptr_coin->setAnchorPoint(Vec2(0.5, 0.2));
        m_list_coin.push_back(ptr_coin);
        CCNode::addChild(ptr_coin, 0, -1);
        ptr_coin->setVisible(false);
    }

    setVisible(true);
    setTouchEnabled(false);
    sptr_gold_rain = this;
    return true;
}
void UIGoldRain::show_glod_rain() {
    Director* ptr_director = Director::getInstance();
    Size the_director_size = ptr_director->getVisibleSize();

//	SimpleAudioEngine::getInstance()->playEffect(CCFileUtils::getInstance()->fullPathForFilename("music/goldFall.mp3").c_str());
    HN::HNAudioEngine::getInstance()->playEffect(CCFileUtils::getInstance()->fullPathForFilename("music/goldFall.mp3").c_str());

    std::list<UICoin*>::iterator iter = m_list_coin.begin();
    for (iter = m_list_coin.begin(); iter != m_list_coin.end(); iter++) {
        UICoin* ptr_icon = *iter;
        ptr_icon->stopAllActions();
        ptr_icon->Play();
        ptr_icon->setVisible(true);
        int int_pos_x = rand() % ((int)the_director_size.width);
        int int_pos_y = the_director_size.height + 50 + rand() % 100;
        ptr_icon->setPosition(Vec2(int_pos_x, int_pos_y));

        float float_move_time = (float)(rand() % 50) / 100.0f + 0.8f;
        float float_delay_time = (float)(rand() % 150) / 100.0f;
        DelayTime*		ptr_action_0 = DelayTime::create(float_delay_time);
        MoveTo*			ptr_action_1 = MoveTo::create(float_move_time, Vec2(int_pos_x, 0));
        EaseBounceOut *	ptr_action_2 = EaseBounceOut::create(ptr_action_1);
        MoveTo*			ptr_action_3 = MoveTo::create(0.2f, Vec2(int_pos_x, -150));

        CallFuncN*		ptr_action_4 = CallFuncN::create([&,ptr_icon](Node*)->void{
            ptr_icon->stopAllActions();
            ptr_icon->setVisible(false);
        });

        ptr_icon->runAction(CCSequence::create(ptr_action_0, ptr_action_2, ptr_action_3, ptr_action_4, NULL));
    }
}

void UIGoldRain::on_play_finish(Node* ptr_sender) {
    ptr_sender->stopAllActions();
    ptr_sender->setVisible(false);
}
