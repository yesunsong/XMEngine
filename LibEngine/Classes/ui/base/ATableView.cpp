//#include "stdafx.h"
#include "ATableView.h"
#include "test/WireframeOnOff.h"
//#include "test/HNConverCode.h"

namespace HN {

ATableView::ATableView() :
    isDrawRect(false),
    numberOfCells(0),
    cellSize(100,100) {
    setDrawRect(isDrawRect || TABLEVIEW_ONOFF);
}

ATableView::~ATableView() {
}

ATableView* ATableView::create(CreateTableCellCallback createCellCallback) {
    return ATableView::create(nullptr, Size::ZERO, createCellCallback);
}

ATableView* ATableView::create(TableViewDataSource* dataSource, Size size, CreateTableCellCallback createCellCallback) {
    return ATableView::create(dataSource, size, nullptr, createCellCallback);
}

ATableView* ATableView::create(TableViewDataSource* dataSource, Size size, Node *container, CreateTableCellCallback createCellCallback) {
    ATableView *table = new (std::nothrow) ATableView();
    table->createCellCallback = createCellCallback;
    table->setDataSource(dataSource);
    table->init();
    table->initWithViewSize(size, container);
    table->autorelease();
    table->_updateCellPositions();
    table->_updateContentSize();
    return table;
}

bool ATableView::init() {
    if (!TableView::init()) {
        return false;
    }
    setDataSource(this);
    return true;
}

ssize_t ATableView::numberOfCellsInTableView(TableView *table) {
    return numberOfCells;
}

Size ATableView::cellSizeForTable(TableView *table) {
    return cellSize;
}

TableViewCell* ATableView::tableCellAtIndex(TableView *table, ssize_t idx) {
    if (createCellCallback) {
        return createCellCallback(table, idx);
    }
    return nullptr;
}

void ATableView::setATableViewDelegate(ATableViewDelegate* tableDelegate) {
    aTableViewDelegate = tableDelegate;
}

void ATableView::reloadData() {
    //不重置方向进行reload
    for (const auto &cell : _cellsUsed) {
        if (_tableViewDelegate != nullptr) {
            _tableViewDelegate->tableCellWillRecycle(this, cell);
        }

        _cellsFreed.pushBack(cell);

        cell->reset();
        if (cell->getParent() == this->getContainer()) {
            this->getContainer()->removeChild(cell, true);
        }
    }

    _indices->clear();
    _cellsUsed.clear();

    this->_updateCellPositions();
    this->_updateContentSize();
    if (_dataSource->numberOfCellsInTableView(this) > 0) {
        this->scrollViewDidScroll(this);
    }
}

void ATableView::setDrawRect(bool isDraw) {
    this->isDrawRect = isDraw;
}

void ATableView::draw(Renderer *renderer, const Mat4& transform, uint32_t flags) {
    if (isDrawRect) {
        _customCommand.init(_globalZOrder+1);
        _customCommand.func = CC_CALLBACK_0(ATableView::onDrawPrimatives, this, transform, flags);
        renderer->addCommand(&_customCommand);
    }
}

void ATableView::onDrawPrimatives(const cocos2d::Mat4 &transform, uint32_t flags) {
    GraphicsUtils::drawOutline(this->isIgnoreAnchorPointForPosition(), this->getAnchorPoint(), this->getPosition(), this->getViewSize(),this, transform);
}

float ATableView::getLength() {
    if (isVertical()) {
        return numberOfCellsInTableView(this)*tableCellSizeForIndex(this, 0).height;
    } else if (isHorizontal()) {
        return numberOfCellsInTableView(this)*tableCellSizeForIndex(this, 0).width;
    }
    return 0.0f;
}

void ATableView::setNumberOfCellsInTableView(ssize_t value) {
    this->numberOfCells = value;
}

void ATableView::setTableCellSize(Size size) {
    this->cellSize = size;
}


void ATableView::setContentOffsets(int index,bool animated) {
    setContentOffset(calculateTableCellOffsetByCellIdx(numberOfCells, index, 1), false);
}

//allCellsCount:cell的总数
//cellIndexInContent:需要指定的cell的索引，从0开始计数
//cellIndexInView:需要将cellIndex放到可视区域的第几个，从1开始
Vec2 ATableView::calculateTableCellOffsetByCellIdx( int allCellsCount, int cellIndexInContent, int cellIndexInView) {
    float viewWidth = getViewSize().width;//可视区域的宽度
    float viewHeight = getViewSize().height;//可视区域的高度
    float cellWidth = cellSize.width;//单个cell的高度
    float cellHeight = cellSize.height;//单个cell的高度
    int viewCellsCountY = viewHeight / cellHeight;//可视区域可显示的cell的数量
    int viewCellsCountX = viewWidth / cellWidth;//可视区域可显示的cell的数量
    float tableTotalHeight = cellHeight * allCellsCount;
    float tableTotalWidth = cellWidth * allCellsCount;
    if (isVertical()) {
        if (tableTotalHeight > cellHeight) {
            return Vec2(0.0f, 0.0f - (allCellsCount - (cellIndexInContent + viewCellsCountY - cellIndexInView + 1)) * cellHeight);
        } else {
            return Vec2(0.0f, cellHeight - tableTotalHeight);
        }
    } else if(isHorizontal()) {
        if (tableTotalWidth > cellWidth) {
            return Vec2(0.0f - ( (cellIndexInContent + cellIndexInView-1)) * cellWidth, 0.0f);
        } else {
            return Vec2(cellWidth - tableTotalWidth, 0.0f);
        }
    }
    return Vec2::ZERO;
}

bool ATableView::isHorizontal() {
    return (getDirection() == cocos2d::extension::ScrollView::Direction::HORIZONTAL);
}

bool ATableView::isVertical() {
    return (getDirection() == cocos2d::extension::ScrollView::Direction::VERTICAL);
}

}
