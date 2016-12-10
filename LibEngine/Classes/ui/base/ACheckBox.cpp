//#include "stdafx.h"
#include "ACheckBox.h"

namespace HN {
ACheckBox::ACheckBox() {
}

ACheckBox::~ACheckBox() {
}

ACheckBox* ACheckBox::create(const std::string& backGround,
                             const std::string& backGroundSeleted,
                             const std::string& cross,
                             const std::string& backGroundDisabled,
                             const std::string& frontCrossDisabled,
                             TextureResType texType) {
    ACheckBox *pWidget = new (std::nothrow) ACheckBox;
    if (pWidget && pWidget->init(backGround,
                                 backGroundSeleted,
                                 cross,
                                 backGroundDisabled,
                                 frontCrossDisabled,
                                 texType)) {
        pWidget->autorelease();
        return pWidget;
    }
    CC_SAFE_DELETE(pWidget);
    return nullptr;
}

ACheckBox* ACheckBox::create(const std::string& backGround,
                             const std::string& cross,
                             TextureResType texType) {
    ACheckBox *pWidget = new (std::nothrow) ACheckBox;
    if (pWidget && pWidget->init(backGround,
                                 "",
                                 cross,
                                 "",
                                 "",
                                 texType)) {
        pWidget->autorelease();
        return pWidget;
    }
    CC_SAFE_DELETE(pWidget);
    return nullptr;
}

void ACheckBox::seBackGroundSelectedBox(Vec2 pos) {
    _frontCrossRenderer->setPosition(pos);
}

}
