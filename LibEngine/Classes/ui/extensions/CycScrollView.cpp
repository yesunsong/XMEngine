//
//  CycScrollView.cpp
//  LibHNUI
//
//  Created by Sunsong Ye on 16/11/25.
//  Copyright © 2016年 redbird. All rights reserved.
//

#include "CycScrollView.h"
#include "globel\FontSize.h"

void CycScrollView::onExit() {
    Widget::onExit();
}

bool CycScrollView::init() {
    if (!Widget::init()) {
        return false;
    }

    m_ViewSize = Size(1280,720);
    winSize = Director::getInstance()->getWinSize();
    firstNode = nullptr;
    visibleCount = 4;
    isMoveLeft = false;
    isMoveRight = false;
    owner = nullptr;

    return true;
}

void CycScrollView::loadScrollView(std::vector<Button*> listNode,float blankDis) {
    m_blankDis = blankDis;

    int index=0;
    CycNode* prevNode = nullptr;
    for (Button* button : listNode) {//定义成双向链表节点
        CycNode* curNode = new CycNode();
        curNode->node = button;
        curNode->index = index +1;
        //button->setUserData(&curNode);//将节点反向回双向链表
        curNode->preNode = prevNode;

        if (prevNode) {
            prevNode->nextNode = curNode;
        }

        prevNode = curNode;

        if (firstNode == nullptr) {
            firstNode = curNode;
        }

        if (index == listNode.size() - 1) {
            curNode->nextNode = firstNode;
            firstNode->preNode = curNode;
        }

        listData.insert(std::pair <int, CycNode* >(curNode->index,curNode));

        index++;
    }

    index = 0;
    for (cocos2d::ui::Button* n : listNode) {
        n->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        Vec2 target = Vec2(n->getContentSize().width / 2 + index*(n->getContentSize().width + m_blankDis), n->getContentSize().height / 2);
        n->setPosition(target);
        addChild(n);

        Label* label = Label::createWithTTF(StringUtils::format("%d",(index+1)), DEFAULT_FONT, 26);
        n->addChild(label);

        listData.at(index+1)->target = target;
        index++;
    }

    canScroll = true;

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(false);
    listener->onTouchBegan = CC_CALLBACK_2(CycScrollView::touchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(CycScrollView::touchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(CycScrollView::touchEnded,this);
    listener->onTouchCancelled = CC_CALLBACK_2(CycScrollView::touchCanceled,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool CycScrollView::touchBegan(Touch* touch,Event*) {
    isMoveLeft = false;
    isMoveRight = false;
    //停止运动并回到目的地
    for (int i = 0; i < listData.size(); i++) {
        CycNode* node = listData[i];
        if (node) {
            node->node->stopAllActions();
            node->node->setPosition(node->target);
        }
    }
    //
    curPoint = convertToNodeSpace(touch->getLocation());
    startPoint = curPoint;
    selNode = nullptr;
    CycNode* pcurNode = firstNode;
    do {
        Size nodeSize = pcurNode->node->getContentSize();
        Vec2 p = pcurNode->node->getPosition();
        Rect r = Rect(p.x, p.y, nodeSize.width, nodeSize.height);
        if (r.containsPoint(curPoint)) {
            selNode = pcurNode->node;

            if (owner) {
                owner->dragBeginNode(pcurNode->node, touch);
            }
            break;
        }
        pcurNode = pcurNode->nextNode;
    } while (pcurNode != firstNode);

    //}
    if (curPoint.y > 0 && curPoint.y < m_ViewSize.height) {
        return true;
    }
    return false;
}

void CycScrollView::touchEnded(Touch* touch, Event*) {
    Vec2 newPoint = convertToNodeSpace(touch->getLocation());
    //
    //isMoveLeft = false;
    //isMoveRight = false;
    //float deltaX = newPoint.x - startPoint.x;
    //if (deltaX < 0 ) { //向左移
    //    isMoveLeft = true;
    //    isMoveRight = !isMoveLeft;
    //}

    //if (deltaX > 0 ) { //向右移
    //    isMoveLeft = false;
    //    isMoveRight = !isMoveLeft;
    //}
    //
    CycNode* rightNode = getRightNode();

    CycNode* curNode = nullptr;
    CycNode* tmpNode = nullptr;
    if (isMoveRight) {
        curNode = getLeftNode();
        tmpNode = curNode->preNode;
        curNode = tmpNode;
    }

    if (isMoveLeft) {
        curNode = getRightNode();
        tmpNode = curNode->nextNode;
        curNode = tmpNode;
    }

    int index = 0;
    if (isMoveRight) {
        index = 0;
    } else if (isMoveLeft) {
        index = visibleCount -1 ;
    }

    int count = 0;
    do {
        Vec2 target;
        if (isMoveRight) {
            target = Vec2(tmpNode->node->getContentSize().width / 2 + index*(tmpNode->node->getContentSize().width + m_blankDis), tmpNode->node->getPositionY());
        } else if (isMoveLeft) {
            target = Vec2(tmpNode->node->getContentSize().width / 2 + index*(tmpNode->node->getContentSize().width + m_blankDis), tmpNode->node->getPositionY());
        }

        if (tmpNode) {
            tmpNode->target = target;
            tmpNode->node->runAction(Sequence::create(MoveTo::create(0.3f, target), CCCallFunc::create([tmpNode]() {
                log("test %d", tmpNode->index);
            }), nullptr));
            tmpNode->node->setVisible(count <=(visibleCount ));
        }


        if (isMoveRight) {
            index++;
            tmpNode = tmpNode->nextNode;
        } else if (isMoveLeft) {
            index--;
            tmpNode = tmpNode->preNode;
        }

        count++;
    } while (tmpNode != curNode);

    if (owner&&selNode) {
        owner->dragEndNode(selNode, touch);
    }
}

void CycScrollView::touchMoved(Touch* touch, Event*) {
    if (!canScroll) {
        return;
    }

    //isMoveLeft = false;
    //isMoveRight = false;
    //
    //touch->getDelta()
    Vec2 newPoint = convertToNodeSpace(touch->getLocation());
    float deltaX = newPoint.x - curPoint.x;
    curPoint = newPoint;
    log("==============delta x:%f",deltaX);

    CycNode* pmoveFirst = NULL;
    CycNode* pcurNode = this->firstNode;
    int index = 0;
    float y = pcurNode->node->getPositionY();
    if (deltaX < 0 && abs(deltaX) >=1) { //向左移
        isMoveLeft = true;
        isMoveRight = !isMoveLeft;

        float maxX = 0;
        pmoveFirst = getRightNode();
        maxX = pmoveFirst->node->getPositionX();
        log("======rightmost index:%d,x:%f", pmoveFirst->index,maxX);
        pmoveFirst->nextNode->node->setPosition(Vec2(maxX + (pmoveFirst->node->getContentSize().width + m_blankDis), y));
    }

    if (deltaX > 0 && abs(deltaX) >= 1) { //向右移
        isMoveLeft = false;
        isMoveRight = !isMoveLeft;

        float minX = m_ViewSize.width;
        pmoveFirst = getLeftNode();
        log("======leftmost index:%d", pmoveFirst->index);
        minX = pmoveFirst->node->getPositionX();
        pmoveFirst->preNode->node->setPosition(Vec2(minX - (pmoveFirst->node->getContentSize().width + m_blankDis), y));
    }

    if (pmoveFirst) {
        pcurNode = pmoveFirst;
        do {
            Vec2 nPoint = (pcurNode->node)->getPosition();
            float newX = nPoint.x + deltaX;
            (pcurNode->node)->setVisible(true);
            (pcurNode->node)->setPosition(Vec2(newX, y));
            pcurNode = pcurNode->nextNode;
        } while (pcurNode != pmoveFirst);
    }
    if (owner&&selNode) {
        owner->dragMoveNode(selNode, touch);
    }

}

void CycScrollView::touchCanceled(Touch* touch,Event*) {
    Vec2 newPoint = convertToNodeSpace(touch->getLocation());
    //
    if(owner && selNode) {
        owner->dragEndNode(selNode, touch);
    }
}

CycNode* CycScrollView::getLeftNode() {
    CycNode* curNode = nullptr ;
    CycNode* tmpNode = firstNode;
    int minX = m_ViewSize.width;
    do {
        Vec2 nPoint = (tmpNode->node)->getPosition();
        float preX = nPoint.x - (tmpNode->node)->getContentSize().width / 2;
        if (preX < minX && preX >= 0) {
            curNode = tmpNode;
            minX = preX;
        }
        tmpNode = tmpNode->nextNode;
    } while (tmpNode != firstNode);

    return curNode;
}

CycNode* CycScrollView::getRightNode() {
    CycNode* curNode = nullptr;
    CycNode* tmpNode = firstNode;
    int maxX = 0;
    do {
        Vec2 nPoint = (tmpNode->node)->getPosition();
        float preX = nPoint.x  + (tmpNode->node)->getContentSize().width/2;
        if (preX > maxX && preX <= m_ViewSize.width) {
            curNode = tmpNode;
            maxX = preX;
        }
        tmpNode = tmpNode->nextNode;
    } while (tmpNode != firstNode);

    return curNode;
}

void CycScrollView::setFirstIndex(int idx) {
    if (idx <0 || idx > listData.size()) {
        return;
    }

    CycNode* firstNode = listData[idx];
    CycNode* tmpNode = firstNode;
    int index = 0;
    do {
        Vec2 target = Vec2(tmpNode->node->getContentSize().width / 2 + index*(tmpNode->node->getContentSize().width + m_blankDis), 0);
        tmpNode->node->runAction(Sequence::create(MoveTo::create(0.3f, target), CCCallFunc::create([tmpNode]() {
            log("test %d", tmpNode->index);
        }), nullptr));
        index++;
        tmpNode = tmpNode->nextNode;
    } while (tmpNode != firstNode);
}