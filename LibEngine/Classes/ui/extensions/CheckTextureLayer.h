#ifndef _CHECK_TEXTURELAYER_H_
#define _CHECK_TEXTURELAYER_H_

#include "UI/Base/HNLayer.h"
#include <stdio.h>
USING_NS_CC;

namespace HN {

class CheckTextureLayer : public HNLayer {
public:
    CheckTextureLayer();
    ~CheckTextureLayer();
    CREATE_FUNC(CheckTextureLayer);
    virtual bool init() override;

    void readTxt();
    void checkName(string& name);
public:
    virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;
    virtual void onTouchMoved(Touch *touch, Event *unused_event) override;
    virtual void onTouchEnded(Touch *touch, Event *unused_event) override;

private:
    void split(std::string &s, std::string &delim, std::vector<std::string> &ret);
    void refreshList();
    void createList();
    vector<Sprite *> list;
    vector<Label *> intros;
    Size winSize;
    Vec2 beginPostion;
    //是否有移动过
    bool isMoved;
    //点击屏幕上区域的次数
    unsigned int downCount;
    //点击屏幕下区域的次数
    unsigned int upCount;
};
}
#endif /* _CHECK_TEXTURELAYER_H_ */
