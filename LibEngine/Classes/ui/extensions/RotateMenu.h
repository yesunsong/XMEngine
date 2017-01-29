#ifndef  __ROTATE_MENU_H__
#define __ROTATE_MENU_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

using namespace ui;
/*
*模仿乱斗西游主界面的旋转菜单
*/
class RotateMenu :public cocos2d::Layer {
public:
    RotateMenu();
    //构造方法
    CREATE_FUNC(RotateMenu);
    //添加菜单项
    void addMenuItem(Button *item,int i);
    //更新位置
    void updatePosition();
    //更新位置，有动画
    void updatePositionWithAnimation();
    //位置矫正  修改角度 forward为移动方向  当超过1/3，进1
    //true 为正向  false 负
    void rectify(bool forward);
    //初始化
    virtual bool init();
    //重置  操作有旋转角度设为0
    void reset();

    bool IsMoveded() {
        return _isMove;
    };

    void setClickButton(bool flag);
private:
    //设置角度 弧度
    void setAngle(float angle);
    float getAngle();
    //设置单位角度 弧度
    void setUnitAngle(float angle);
    float getUnitAngle();
    //滑动距离转换角度,转换策略为  移动半个Menu.width等于_unitAngle
    float disToAngle(float dis);
    //返回被选中的item
    Button * getCurrentItem();

    void autoMove(float dt);
    void stopMove(float dt);
private:
    //菜单已经旋转角度 弧度
    float _angle;
    //菜单项集合,_children顺序会变化，新建数组保存顺序
    cocos2d::Vector<Button *> _items;
    //单位角度 弧度
    float _unitAngle;
    //监听函数
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    //动画完结调用函数
    void actionEndCallBack(float dx);
    //当前被选择的item
    Button *_selectedItem;
    //动画运行时间
    float animationDuration = 0.0001f;
    float animationDurationEnded = 0.00001f;
    bool _isMove;
    bool _isClick;
    bool m_autoMove;
    bool _canStop;
    int tag;
    int _canStopCount = 0;
};

#endif
