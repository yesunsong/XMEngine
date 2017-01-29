#include "TableViewTest.h"
#include "ui\base\ATableView.h"
#include "ui\base\BTableView.h"
#include "framework\testResource.h"
#include "globel\ApplicationMacro.h"
#include "test\HNConverCode.h"

using namespace HN;

TableViewTests::TableViewTests() {
    ADD_TEST_CASE(BaseTableViewTest);
    ADD_TEST_CASE(BTableViewTest);
}

//------------------------------------------------------------------
//
// BaseTableViewTest
//
//------------------------------------------------------------------

BaseTableViewTest::BaseTableViewTest(void) {
}

BaseTableViewTest::~BaseTableViewTest(void) {
}


void BaseTableViewTest::onEnter() {
    TestCase::onEnter();
    testATableView();
}

void BaseTableViewTest::testATableView() {
    CreateTableCellCallback callback = [&](TableView *table,
    ssize_t idx) -> TableViewCell * {
        TableViewCell *Cell = table->dequeueCell();
        if (!Cell) {
            Cell = new TableViewCell();
            Cell->autorelease();
        }
        Cell->removeAllChildrenWithCleanup(false);
        //获取size的大小
        Size size = (dynamic_cast<ATableView *>(table))->cellSizeForTable(table);
        return Cell;
    };

    ATableView *tableView = ATableView::create(callback);
    tableView->setViewSize(WIN_SIZE);
    tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    tableView->setPosition(Vec2(200, 200));
    tableView->setNumberOfCellsInTableView(10);
    tableView->reloadData();
    addChild(tableView);
}

std::string BaseTableViewTest::title() const {
    return "TableView Test";
}
std::string BaseTableViewTest::subtitle() const {
    return "Base TableView Test";
}


//------------------------------------------------------------------
//
// BTableViewTest
//
//------------------------------------------------------------------

BTableViewTest::BTableViewTest(void) {
}

BTableViewTest::~BTableViewTest(void) {
}


void BTableViewTest::onEnter() {
    TestCase::onEnter();
    testBTableView();
}

void BTableViewTest::testBTableView() {
    BTableView *m_pTableView = BTableView::createWithSlider(
                                   BRNN_SET_SCROLL_BAR_BG, BRNN_SET_SCROLL_BAR_FOREBG,
                                   BRNN_SET_SCROLL_BAR_BALL,
    [](TableView *table, ssize_t idx) -> TableViewCell * {
        TableViewCell *Cell = table->dequeueCell();
        if (!Cell) {
            Cell = new TableViewCell();
            Cell->autorelease();
        }
        Cell->removeAllChildrenWithCleanup(true);
        //获取size的大小
        Size size =
        (dynamic_cast<ATableView *>(table))->cellSizeForTable(table);

        auto name = Label::create(GBKToUtf8(StringUtils::format("中国人-%d", idx).c_str()), "", 25);
        name->setColor(Color3B::RED);
        name->setPosition((size.width / 2), (size.height / 2));
        Cell->addChild(name);
        return Cell;
    });
    m_pTableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);

    // BTW:这几个顺序不能反过来
    // setDirection
    // setPosition
    // setViewSize
    // reloadData
    int num = 5;
    float cellWidth = 120;
    float cellHeight = 120;
    float viewWidth = cellWidth * num;
    float viewHeight = cellHeight * num;

    if (m_pTableView->getTable()->isVertical()) {
        m_pTableView->setPosition(0, 100);
        m_pTableView->setViewSize(Size(viewWidth, viewHeight));
        m_pTableView->setTableCellSize(Size(viewWidth, cellHeight));
    } else if (m_pTableView->getTable()->isHorizontal()) {
        m_pTableView->setPosition(100, 200);
        m_pTableView->setViewSize(Size(viewWidth, 50));
        m_pTableView->setTableCellSize(Size(cellWidth, 50));
    }
    m_pTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    m_pTableView->setProgressOpacity(0);
    m_pTableView->setNumberOfCellsInTableView(10);
    m_pTableView->reloadData();
    m_pTableView->getSlider()->setValue(0.0f);
    this->addChild(m_pTableView);
}

std::string BTableViewTest::title() const {
    return "TableView Test";
}

std::string BTableViewTest::subtitle() const {
    return "BTableView Test";
}