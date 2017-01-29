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
#include "2d/CCActionTween.h"

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
    Button* node; //所对应的Node
    CycNode* nextNode;//后一个节点
    int index;
    Vec2 target;
};

class CycScrollView : public Widget {
    CC_SYNTHESIZE(CycScrollDelegate*, owner, Owner);

public:
    virtual void onExit();
    virtual bool init();
    CREATE_FUNC(CycScrollView);

public:
    void loadScrollView(std::vector<Button*> listNode,float blankDis); //真实加载循环滚动条中的Vector文件
    void setFirstIndex(int index);

private:
    Vec2 curPoint;

    CycNode* firstNode;
    cocos2d::Node* selNode;

    bool canScroll;

    Size winSize;
    Point beganPoint;
    Size m_ViewSize;

    int m_blankDis;

    std::map<int,CycNode*> listData;

    bool touchBegan(Touch* touch,Event*);
    void touchEnded(Touch* touch,Event*);
    void touchMoved(Touch* touch,Event*);
    void touchCanceled(Touch* touch,Event*);
    CycNode* getLeftNode();

    CycNode* getRightNode();
    int visibleCount;
    bool isMoveLeft;
    bool isMoveRight;
    //float deltaX;
    cocos2d::Vec2 startPoint;
};

#endif /* CycScrollView_h */
