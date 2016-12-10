//
//  TextureLayer.hpp
//  LibHNUI
//
//  Created by Sunsong Ye on 16/9/1.
//  Copyright © 2016年 redbird. All rights reserved.
//

#ifndef TextureLayer_hpp
#define TextureLayer_hpp

#include "ui/base/HNLayer.h"
#include "cocos2d.h"
#include <stdio.h>
USING_NS_CC;

namespace HN {

class TextureLayer : public HNLayer {
public:
    TextureLayer();
    ~TextureLayer();
    CREATE_FUNC(TextureLayer);
    virtual bool init() override;

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
#endif /* TextureLayer_hpp */
