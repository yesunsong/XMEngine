#ifndef _dropdown_list_
#define _dropdown_list_

#include "ui/base/HNLayer.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/base/AControlButton.h"

USING_NS_CC;
using namespace extension;

namespace HN {

enum DropdownListTag {
    DL_HelpBtn,
    DL_SetBtn,
    DL_LeaveBtn,
    DL_NextRoundExitBtn,
};

class DropdownList :public HNLayer {
public:
    DropdownList();
    virtual ~DropdownList();
    bool onTouchBegan(Touch *touch, Event *unused_event)override;
    void onTouchEnded(Touch *touch, Event *unused_event)override;
    void changeCheckBox();
    void setSetBtnCallback(cocos2d::extension::Control::Handler handle);
    void setLeaveBtnCallback(cocos2d::extension::Control::Handler handle);
    void setNextRoundBtnCallback(cocos2d::extension::Control::Handler handle);
    void setHelpBtnCallback(cocos2d::extension::Control::Handler handle);
    CREATE_FUNC(DropdownList);

    virtual bool init()override;

public:
    bool isSelectedBox();

private:
    AControlButton*  setBtn;
    AControlButton*  helpBtn;
    AControlButton*  leaveBtn;
    AControlButton*  nextRoundOutBtn;
    Sprite* checkSprite;
    bool isSelected;
};

}

#endif //_dropdown_list_
