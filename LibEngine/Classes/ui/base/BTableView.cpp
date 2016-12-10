//#include "stdafx.h"
#include "BTableView.h"
//#include "test/HNLog.h"

namespace HN {
bool BTableView::initWithSlider(const char* bgFile, const char* progressFile, const char* thumbFile, CreateTableCellCallback createCellCallback) {
    if (!Node::init()) {
        return false;
    }

    Size winSize = Director::getInstance()->getWinSize();
    table = ATableView::create(createCellCallback);
    table->setDelegate(this);
    table->setATableViewDelegate(this);
    table->reloadData();
    addChild(table);

    progressBarBg = Sprite::create(bgFile);
    progressBarBg->setRotation(90);
    addChild(progressBarBg);

    slider = ASlider::create(progressFile, bgFile, thumbFile);
    slider->setPosition(Vec2::ZERO);
    slider->setMinimumValue(0);
    slider->setMaximumValue(100);
    slider->setRotation(90);
    slider->setOffsetX(30);
    slider->setMaskDiff(15);
    slider->setProgressSpritePositionX(20);
    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(BTableView::sliderCallback), Control::EventType::VALUE_CHANGED);
    ATableView* tmp = table;
    bool isTmp = isEnd;
    slider->setSliderEndedCallback([tmp]() {
        //HNLOG("end callback");
    });
    addChild(slider);
    return true;
}

void BTableView::sliderCallback(Ref* pSender, Control::EventType type) {
    ASlider* pSlider = static_cast<ASlider*>(pSender);
    if (!pSlider->getTouchBegan()) {
        if (pSlider->isSelected()) {
            float off = getOffset();
            float newY = 0.0f;
            //HNLOG("-----slider is selected:%d", pSlider->isSelected());
            if (table->isVertical()) {
                newY = -off*(1 - pSlider->getValue() / 100);
            } else {
                newY = -off*( pSlider->getValue() / 100);
            }
            //HNLOG("-----slider value:%f,table x/y:%f/%f", pSlider->getValue(), newY);
            if (table->isVertical()) {
                table->getContainer()->setPositionY(newY);
            } else if (table->isHorizontal()) {
                table->getContainer()->setPositionX(newY);
            }
            table->reloadData();
        }
    }
}

//////////////////////////////////////////////////////////////////////////

void BTableView::setNumberOfCellsInTableView(ssize_t value) {
    table->setNumberOfCellsInTableView(value);
}

void BTableView::setTableCellSize(Size size) {
    table->setTableCellSize(size);
}

void BTableView::setCreateTableCell(CreateTableCellCallback callback) {
    table->createCellCallback = callback;
}

TableViewCell* BTableView::tableCellAtIndex(TableView *table, ssize_t idx) {
    TableViewCell * Cell = table->dequeueCell();
    return Cell;
}

void BTableView::tableCellTouched(TableView* table, TableViewCell* cell) {
}

void BTableView::scrollViewDidScroll(cocos2d::extension::ScrollView* view) {
    if (!slider->isSelected()) {
        float off = getOffset();
        float percent = 0.0f;
        if (table->isVertical()) {
            percent = 1 - abs(table->getContainer()->getPositionY()) / off;
        } else if (table->isHorizontal()) {
            percent = abs(table->getContainer()->getPositionX()) / off;
        }
        //HNLOG("-----table percent=%f,x/y:%f/%f", percent, table->getContainer()->getPositionX(),table->getContainer()->getPositionY());
        slider->setValue(percent * 100);
    }
}

float BTableView::getOffset() {
    return (table->getLength() - table->getViewSize().width);
}

//////////////////////////////////////////////////////////////////////////

void BTableView::setDirection(TableView::Direction Direction) {
    table->setDirection(Direction);
    if (table->isVertical()) {
        //slider->setRotation(270.0f);
        //progressBarBg->setRotation(270.0f);

        slider->setRotation(90.0f);
        progressBarBg->setRotation(90.0f);
    } else if(table->isHorizontal()) {
        slider->setRotation(0.0f);
        progressBarBg->setRotation(0.0f);
    }
}

void BTableView::setVerticalFillOrder(TableView::VerticalFillOrder fillOrder) {
    table->setVerticalFillOrder(fillOrder);
    table->reloadData();
}


void BTableView::setViewSize(Size size) {
    table->setViewSize(size);
    table->setVisible(true);

    if (table->isHorizontal()) {
        progressBarBg->setPosition(Vec2(table->getPositionX()+(table->getViewSize().width-slider->getContentSize().height)/2 , table->getPositionY() - table->getViewSize().height));
    } else  if(table->isVertical()) {
        progressBarBg->setPosition(Vec2(table->getPositionX() + table->getViewSize().width + progressBarBg->getContentSize().height / 2, table->getPositionY() + table->getViewSize().height / 2));
    }
    slider->setPosition(Vec2(progressBarBg->getPositionX(), progressBarBg->getPositionY()));
}

void BTableView::reloadData() {
    table->reloadData();
    table->setContentOffset(table->calculateTableCellOffsetByCellIdx(table->numberOfCells, 0, 1), false);
}

void BTableView::setPosition(const Vec2 &position) {
    setPosition(position.x, position.y);
}

void BTableView::setPosition(float x, float y) {
    table->setPosition(table->getPosition() + Vec2(x, y));
    progressBarBg->setPosition(Vec2(table->getPositionX() + table->getViewSize().width + progressBarBg->getContentSize().height / 2, table->getPositionY() + table->getViewSize().height / 2));
    slider->setPosition(Vec2(progressBarBg->getPositionX(), progressBarBg->getPositionY() ));//- slider->getThumbSprite()->getContentSize().width / 2
}

void BTableView::setSliderScaleY(float scaleY) {
    if (slider) {
        slider->setScaleX(scaleY);
    }
    if (progressBarBg) {
        progressBarBg->setScaleX(scaleY);
    }
}

void BTableView::setProgressOpacity(GLubyte opacity) {
    slider->getProgressSprite()->setOpacity(opacity);
    slider->getBackgroundSprite()->setOpacity(opacity);
}

}
