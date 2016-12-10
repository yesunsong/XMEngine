//
//  CycScrollView.hpp
//  LibHNUI
//
//  Created by Sunsong Ye on 16/11/25.
//  Copyright © 2016年 redbird. All rights reserved.
//

#ifndef CycScrollView_h
#define CycScrollView_h

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGui.h"

USING_NS_CC;
using namespace cocos2d::ui;

class CycScrollDelegate {
public:
    virtual void dragBeginNode(cocos2d::Node* node,cocos2d::Touch* touch) = 0; //开始拖拽时拖拽的节点
    virtual void dragMoveNode(cocos2d::Node* node,cocos2d::Touch* touch) = 0; //拖拽移动时拖拽的节点
    virtual void dragEndNode(cocos2d::Node* node,cocos2d::Touch* touch) = 0; //拖拽结束后拖拽的节点
};

struct CycNode { //构建双向链表结构
    CycNode* preNode;//前一个节点
    ImageView* node; //所对应的Node
    CycNode* nextNode;//后一个节点
};

class CycScrollView:public Widget {
    CC_SYNTHESIZE(float, scrollHeight, ScrollHeight);//设置滚动时的高度限制 CC_SYNTHESIZE(CycScrollDelegate*, owerner, Owerner);


public:
    virtual void onExit()override;
    virtual bool init()override;
    CREATE_FUNC(CycScrollView);

public:
    void loadScrollView(std::vector<ImageView*> listNode); //真实加载循环滚动条中的Vector文件
    void setOwner(CycScrollDelegate* owerner);
private:
    CycNode* pFirstCycNode;
    cocos2d::Node* selNode;

    Size winSize;
    bool canScroll;
    int  C_WIDTH =200 ;
    Point curPoint;
    CycScrollDelegate* owerner;

    bool touchBegan(Touch* touch,Event*);
    void touchEnded(Touch* touch,Event*);
    void touchMoved(Touch* touch,Event*);
    void touchCanceled(Touch* touch,Event*);

};

#endif /* CycScrollView_h */
