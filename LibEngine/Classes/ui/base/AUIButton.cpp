//#include "stdafx.h"
#include "AUIButton.h"
#include "render/GraphicsUtils.h"
#include "test/WireframeOnOff.h"


namespace HN {
AUIButton::AUIButton():
    _drawRect(false) {
    setDrawRect(_drawRect || BUTTON_ONOFF);
}

AUIButton::~AUIButton() {
}

AUIButton* AUIButton::create(const std::string &normalImage,
                             const std::string& selectedImage,
                             const std::string& disableImage,
                             TextureResType texType) {
    AUIButton *btn = new (std::nothrow) AUIButton;
    if (btn && btn->init(normalImage, selectedImage, disableImage, texType)) {
        btn->autorelease();
        return btn;
    }
    CC_SAFE_DELETE(btn);
    return nullptr;
}

bool AUIButton::init() {
    if (!Button::init()) {
        return false;
    }
    return true;
}

bool AUIButton::init(const std::string& normalImage,
                     const std::string& selectedImage ,
                     const std::string& disableImage ,
                     TextureResType texType ) {
    if (!Button::init(normalImage, selectedImage, disableImage, texType)) {
        return false;
    }
    return true;
}

void AUIButton::onPressStateChangedToNormal() {
    Button::onPressStateChangedToNormal();
    //this->setScale(_normalTextureScaleXInSize, _normalTextureScaleYInSize);
    for (int i = 0; i < _children.size(); i++) {
        Node* node = _children.at(i);
        //node->setScale(_normalTextureScaleXInSize, _normalTextureScaleYInSize);
    }
}

void AUIButton::onPressStateChangedToPressed() {
    Button::onPressStateChangedToPressed();
    //this->setScale(_pressedTextureScaleXInSize + _zoomScale, _pressedTextureScaleYInSize + _zoomScale);
    for (int i = 0; i < _children.size(); i++) {
        Node* node = _children.at(i);
        //Action *zoomAction = ScaleTo::create(0.05f,
        //	_pressedTextureScaleXInSize + _zoomScale,
        //	_pressedTextureScaleYInSize + _zoomScale);
        //node->runAction(zoomAction);
    }
}

void AUIButton::setGray(bool isGray) {
    if (isGray) {
        gray();
    } else {
        recovery();
    }
}

void AUIButton::gray() {
    GraphicsUtils::gray(_children);
    _buttonNormalRenderer->setState(cocos2d::ui::Scale9Sprite::State::GRAY);
    _buttonClickedRenderer->setState(cocos2d::ui::Scale9Sprite::State::GRAY);
    _buttonDisabledRenderer->setState(cocos2d::ui::Scale9Sprite::State::GRAY);
}

void AUIButton::recovery() {
    GraphicsUtils::recovery(_children);
    _buttonNormalRenderer->setState(cocos2d::ui::Scale9Sprite::State::NORMAL);
    _buttonClickedRenderer->setState(cocos2d::ui::Scale9Sprite::State::NORMAL);
    _buttonDisabledRenderer->setState(cocos2d::ui::Scale9Sprite::State::NORMAL);
}

void AUIButton::setTitle(const std::string &imageFileName) {
    _title = Sprite::create(imageFileName.c_str());
    _title->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 2));
    addChild(_title);
}

void AUIButton::setTitleOffset(Vec2 off) {
    _title->setPosition(_title->getPosition() + off);
}

void AUIButton::draw(Renderer *renderer, const Mat4& transform, uint32_t flags) {
    if (_drawRect) {
        _customCommand.init(_globalZOrder + 1);
        _customCommand.func = CC_CALLBACK_0(AUIButton::onDrawPrimatives, this, transform, flags);
        renderer->addCommand(&_customCommand);
    }
}

void AUIButton::onDrawPrimatives(const cocos2d::Mat4 &transform, uint32_t flags) {
    GraphicsUtils::drawOutline(this->isIgnoreAnchorPointForPosition(), this->getAnchorPoint(), this->getPosition(), this->getContentSize(), this, transform);
}
}
