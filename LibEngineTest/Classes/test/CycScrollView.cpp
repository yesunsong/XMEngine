//
//  CycScrollView.cpp
//  LibHNUI
//
//  Created by Sunsong Ye on 16/11/25.
//  Copyright © 2016年 redbird. All rights reserved.
//

#include "CycScrollView.h"


void CycScrollView::onExit() {
    Widget::onExit();

}

bool CycScrollView::init() {
    if (!Widget::init()) {
        return false;
    }
    scrollHeight = 720;

    return true;
}


void CycScrollView::loadScrollView(std::vector<ImageView*> listNode) {
    CycNode* pcycNode =nullptr;

    for (ImageView* n: listNode) {//定义成双向链表节点
        CycNode* cycnode = new CycNode();
        cycnode->node = n;
        n->setUserData(&cycnode);//将节点反向回双向链表

        cycnode->preNode = pcycNode;
        if(pcycNode) {
            pcycNode->nextNode = cycnode;

        }
        pcycNode = cycnode;

        if(pFirstCycNode == NULL) {
            pFirstCycNode = cycnode;

        }
    }


    int index=0;
    for (ImageView* n: listNode) {
        n->setAnchorPoint(Point::ZERO);
        n->setPosition(Point(index*C_WIDTH,0));
        addChild(n);
        index++;
    }

    canScroll = C_WIDTH*listNode.size()>winSize.width;//设定是否需要循环滚动，如果小于可视化大小的话，则不需要滚动。
    canScroll =true;
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(CycScrollView::touchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(CycScrollView::touchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(CycScrollView::onTouchEnded,this);
    listener->onTouchCancelled = CC_CALLBACK_2(CycScrollView::touchCanceled,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


bool CycScrollView::touchBegan(Touch* touch,Event*) {
    curPoint = touch->getLocation();
    curPoint = convertToNodeSpace(curPoint);

    selNode = nullptr;

    if(owerner) {
        CycNode* pcurNode = pFirstCycNode;
        do {
            Size nodeSize = pcurNode->node->getSize();
            Point p = pcurNode->node->getPosition();
            Rect r = Rect(p.x, p.y, nodeSize.width, nodeSize.height);

            if(r.containsPoint(curPoint)) {
                selNode = pcurNode->node;
                owerner->dragBeginNode(pcurNode->node, touch);
                break;
            }
            pcurNode=pcurNode->nextNode;

        } while (pcurNode != pFirstCycNode);
    }

    if(curPoint.y>0 && curPoint.y < scrollHeight) {
        return true;
    }
    return false;
}

void CycScrollView::touchEnded(Touch* touch,Event*) {
    Point newPoint = touch->getLocation();
    newPoint = convertToNodeSpace(newPoint);

    if(owerner && selNode) {
        owerner->dragEndNode(selNode, touch);
    }
}

void CycScrollView::touchMoved(Touch* touch,Event*) {
    if(!canScroll) {
        return;
    }

    Point newPoint = touch->getLocation();
    newPoint = convertToNodeSpace(newPoint);

    float deltaX = newPoint.x - curPoint.x;
    CycNode* pmoveFirst = NULL;
    CycNode* pcurNode = this->pFirstCycNode;

    int index = 0;
    float y;
    if(deltaX < 0) { //向左移
        float maxX = 0;
        do {
            Point nPoint = (pcurNode->node)->getPosition();
            float preX = nPoint.x;
            if(preX > maxX && preX <= winSize.width) {
                pmoveFirst = pcurNode;
                maxX = preX;
                y = nPoint.y;
            }
            index++;
            pcurNode = pcurNode->nextNode;

        } while (pcurNode!=pFirstCycNode);

        pmoveFirst->nextNode->node->setPosition(Point(maxX+C_WIDTH,y));
    }

    if(deltaX > 0) { //向右移
        float minX = 1200;
        float y;
        do {
            Point nPoint = (pcurNode->node)->getPosition();
            float preX = nPoint.x;
            if(preX < minX && preX>=0) {
                pmoveFirst = pcurNode;
                minX = preX;
                y = nPoint.y;
            }
            index++;
            pcurNode = pcurNode->nextNode;

        } while (pcurNode != pFirstCycNode);
        pmoveFirst->preNode->node->setPosition(Point(minX-C_WIDTH,y));
    }

    //移动
    if(pmoveFirst) {
        pcurNode = pmoveFirst;
        do {
            Point nPoint = (pcurNode->node)->getPosition();
            float newX = nPoint.x + deltaX;
            (pcurNode->node)->setPosition(Point(newX,y));
            pcurNode = pcurNode->nextNode;

        } while (pcurNode != pmoveFirst);
    }

    if(owerner && selNode) {
        owerner->dragMoveNode(selNode, touch);
    }

    curPoint = newPoint;
}

void CycScrollView::touchCanceled(Touch* touch,Event*) {
    Point newPoint = touch->getLocation();
    newPoint = convertToNodeSpace(newPoint);

    if(owerner&&selNode) {
        owerner->dragEndNode(selNode, touch);
    }
}

void CycScrollView::setOwner(CycScrollDelegate* owerner) {
    this->owerner = owerner;
}
