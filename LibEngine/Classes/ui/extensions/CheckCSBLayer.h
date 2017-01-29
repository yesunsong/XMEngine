#ifndef _CHECK_CSB_H_
#define _CHECK_CSB_H_

#include "UI/Base/HNLayer.h"
#include <stdio.h>
USING_NS_CC;

namespace HN {

class CheckCSBLayer : public HNLayer {
public:
    CheckCSBLayer();
    ~CheckCSBLayer();
    CREATE_FUNC(CheckCSBLayer);
    virtual bool init() override;

    void readTxt();
    void checkName(string& name);
public:
    virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;
    virtual void onTouchMoved(Touch *touch, Event *unused_event) override;
    virtual void onTouchEnded(Touch *touch, Event *unused_event) override;

private:
    void split(std::string &s, std::string &delim, std::vector<std::string> &ret);
    vector<Node *> list;
    vector<Label *> intros;
    Vec2 beginPostion;
    //是否有移动过
    bool isMoved;
    //点击屏幕上区域的次数
    unsigned int downCount;
    //点击屏幕下区域的次数
    unsigned int upCount;
};
}
#endif /* _CHECK_CSB_H_ */
