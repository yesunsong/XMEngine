#ifndef _TABLEVIEW_TEST_H_
#define _TABLEVIEW_TEST_H_

#include "framework\BaseTest.h"

DEFINE_TEST_SUITE(TableViewTests);

class BaseTableViewTest : public TestCase {
public:
    BaseTableViewTest();
    ~BaseTableViewTest();
    CREATE_FUNC(BaseTableViewTest);

public:
    virtual void onEnter() override;
    void testATableView();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};


class BTableViewTest : public TestCase {
public:
    BTableViewTest();
    ~BTableViewTest();
    CREATE_FUNC(BTableViewTest);

public:
    virtual void onEnter() override;
    void testBTableView();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif ///_TABLEVIEW_TEST_H_