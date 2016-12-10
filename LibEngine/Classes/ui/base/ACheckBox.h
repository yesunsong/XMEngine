#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

namespace HN {
class ACheckBox :public CheckBox {
public:
    ACheckBox();
    virtual ~ACheckBox();

public:
    static ACheckBox* create(const std::string& backGround,
                             const std::string& backGroundSeleted,
                             const std::string& cross,
                             const std::string& backGroundDisabled,
                             const std::string& frontCrossDisabled,
                             TextureResType texType = TextureResType::LOCAL);

    static ACheckBox* create(const std::string& backGround,
                             const std::string& cross,
                             TextureResType texType = TextureResType::LOCAL);

public:
    void seBackGroundSelectedBox(Vec2 pos);

};

}