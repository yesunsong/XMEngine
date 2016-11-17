#ifndef __H_BTABLEVIEW_H__
#define __H_BTABLEVIEW_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

#include "ASlider.h"
#include "render/GraphicsUtils.h"
#include "ATableView.h"
#include "ATableViewDelegate.h"
//#include "test/HNConverCode.h"


USING_NS_CC;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

#define CREATE_BTABLEVIEW(__TYPE__) \
static __TYPE__* createWithSlider(const char* bgFile, const char* progressFile, const char* thumbFile, CreateTableCellCallback createCellCallback) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->initWithSlider(bgFile, progressFile, thumbFile,createCellCallback)) \
				    { \
        pRet->autorelease(); \
        return pRet; \
				    } \
															    else \
    { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \
}

namespace HN {
class BTableView :public Node, public TableViewDelegate,public ATableViewDelegate {
public:
    typedef std::function<TableViewCell*(TableView *table, ssize_t idx)> CreateTableCellCallback;
    CreateTableCellCallback createCellCallback;

    void setDirection(TableView::Direction Direction);
    void setVerticalFillOrder(TableView::VerticalFillOrder fillOrder);
    // 先要设置位置，然后才可以调用此方法.
    void setViewSize(Size size);
    //
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    //
    virtual void tableCellTouched(TableView* table, TableViewCell* cell)override;
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view)override;
    float getOffset();
    //
    virtual void setPosition(const Vec2 &position)override;
    void setSliderScaleY(float scaleY);
    void setProgressOpacity(GLubyte opacity);
    virtual void setPosition(float x, float y)override;
public:
    CREATE_BTABLEVIEW(BTableView)
    virtual bool initWithSlider(const char* bgFile, const char* progressFile, const char* thumbFile, CreateTableCellCallback createCellCallback);
    void sliderCallback(Ref* pSender, Control::EventType type);
    void setNumberOfCellsInTableView(ssize_t value);
    void setTableCellSize(Size size);
    void setCreateTableCell(CreateTableCellCallback callback);

    void reloadData();
private:
    //ATableView* table;
    //ASlider* slider;
    Sprite* progressBarBg;

    CC_SYNTHESIZE_READONLY(ATableView*, table, Table);
    CC_SYNTHESIZE_READONLY(ASlider*, slider, Slider);

private:
    ASlider* m_slider;
    bool			isDrawRect;
    bool isEnd;
};



}
#endif //__H_BTABLEVIEW_H__

