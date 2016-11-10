#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace ui;


class UICoin;
class UIGoldRain : public Layout {
public:
    UIGoldRain();
    ~UIGoldRain();
public:
    static void	ShowGoldRain(Scene* parent);
    virtual bool init();
    CREATE_FUNC(UIGoldRain);
    void on_play_finish(Node* ptr_sender);
public:
    void show_glod_rain();
    std::list<UICoin*>  m_list_coin;
};
