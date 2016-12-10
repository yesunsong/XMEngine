#ifndef __H_ATABLEVIEW_H__
#define __H_ATABLEVIEW_H__

#include "ASlider.h"
#include "ATableViewDelegate.h"
#include "render/GraphicsUtils.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
//#include "../extensions/GUI/CCScrollView/CCTableView.h"

#pragma warning(disable : 4996)

USING_NS_CC;
using namespace cocos2d::extension;

namespace HN {

typedef std::function<TableViewCell *(TableView *table, ssize_t idx)>
CreateTableCellCallback;

class ATableView : public TableView, public TableViewDataSource {
public:
    ATableView();
    virtual ~ATableView();

    CreateTableCellCallback createCellCallback;
    //
    virtual Size cellSizeForTable(TableView *table) override;
    virtual ssize_t numberOfCellsInTableView(TableView *table) override;
    virtual TableViewCell *tableCellAtIndex(TableView *table,
                                            ssize_t idx) override;
    void setATableViewDelegate(ATableViewDelegate *tableDelegate);
    //
    void reloadData();
    //
    virtual void draw(Renderer *renderer, const Mat4 &transform,
                      uint32_t flags) override;
    void onDrawPrimatives(const cocos2d::Mat4 &transform, uint32_t flags);

    ssize_t numberOfCells;
    void setTableCellSize(Size size);
    void setContentOffsets(int index, bool animated = false);
    Vec2 calculateTableCellOffsetByCellIdx(int allCellsCount,
                                           int cellIndexInContent,
                                           int cellIndexInView);
    bool isHorizontal();
    bool isVertical();
    cocos2d::Size cellSize;

public:
    static ATableView *create(CreateTableCellCallback createCellCallback);
    static ATableView *create(TableViewDataSource *dataSource, Size size,
                              Node *container,
                              CreateTableCellCallback createCellCallback);
    static ATableView *create(TableViewDataSource *dataSource, Size size,
                              CreateTableCellCallback createCellCallback);
    virtual bool init() override;
    void setDrawRect(bool isDraw);

    float getLength();

private:
    CustomCommand _customCommand;

private:
    ASlider *m_slider;
    bool isDrawRect;
    ATableViewDelegate *aTableViewDelegate;

public:
    void setNumberOfCellsInTableView(ssize_t value);
};
}
#endif //__H_ATABLEVIEW_H__