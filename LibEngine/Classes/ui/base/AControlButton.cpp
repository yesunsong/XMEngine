//#include "stdafx.h"
#include "AControlButton.h"
#include "test/WireframeOnOff.h"
#include "HNEngineExport.h"

namespace HN {
AControlButton::AControlButton() :
    _drawRect(false) {
    setDrawRect(_drawRect || BUTTON_ONOFF);
}

AControlButton::~AControlButton() {
}

AControlButton* AControlButton::create() {
    AControlButton *pControlButton = new (std::nothrow) AControlButton();
    if (pControlButton && pControlButton->init()) {
        pControlButton->autorelease();
        return pControlButton;
    }
    CC_SAFE_DELETE(pControlButton);
    return nullptr;
}

AControlButton* AControlButton::create(const char* filename) {
    cocos2d::ui::Scale9Sprite* sprite = cocos2d::ui::Scale9Sprite::create(filename);
    CCASSERT(sprite != nullptr, "filename is invalid");
    return create(sprite);
}

AControlButton* AControlButton::create(cocos2d::ui::Scale9Sprite* sprite) {
    AControlButton *pRet = new (std::nothrow) AControlButton();
    if (pRet&&pRet->initWithBackgroundSprite(sprite)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

AControlButton* AControlButton::create(Node* label, cocos2d::ui::Scale9Sprite* backgroundSprite) {
    AControlButton *pRet = new (std::nothrow) AControlButton();
    if (pRet&& pRet->initWithLabelAndBackgroundSprite(label, backgroundSprite,true)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return pRet;
}

AControlButton* AControlButton::create(const std::string& title, const std::string& fontName, float fontSize) {
    AControlButton *pRet = new (std::nothrow) AControlButton();
    if (pRet&&pRet->initWithTitleAndFontNameAndFontSize(title, fontName, fontSize)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return pRet;
}

bool AControlButton::initWithBackgroundSprite(cocos2d::ui::Scale9Sprite* sprite) {
    if (!ControlButton::initWithBackgroundSprite(sprite)) {
        return false;
    }
    sprite->setScale9Enabled(false);
    setPreferredSize(sprite->getOriginalSize());
    return true;
}

void AControlButton::setGray(bool isGray) {
    if (isGray) {
        gray();
    } else {
        recovery();
    }
}

void AControlButton::gray() {
    GraphicsUtils::gray(_children);
    getBackgroundSprite()->setState(cocos2d::ui::Scale9Sprite::State::GRAY);
}

void AControlButton::recovery() {
    GraphicsUtils::recovery(_children);
    getBackgroundSprite()->setState(cocos2d::ui::Scale9Sprite::State::NORMAL);
}

void AControlButton::setTitle(const char* filename) {
    _title = Sprite::create(filename);
    _title->setPosition((getContentSize().width) / 2, (getContentSize().height) / 2);
    addChild(_title);
}

void AControlButton::setTitleOffset(Vec2 off) {
    _title->setPosition(_title->getPosition()+off);
}

void AControlButton::draw(Renderer *renderer, const Mat4& transform, uint32_t flags) {
    if (_drawRect) {
        _customCommand.init(_globalZOrder + 1);
        _customCommand.func = CC_CALLBACK_0(AControlButton::onDrawPrimatives, this, transform, flags);
        renderer->addCommand(&_customCommand);
    }
}

void AControlButton::onDrawPrimatives(const cocos2d::Mat4 &transform, uint32_t flags) {
    GraphicsUtils::drawOutline(this->isIgnoreAnchorPointForPosition(), this->getAnchorPoint(), this->getPosition(), this->getContentSize(), this, transform);
}
}
