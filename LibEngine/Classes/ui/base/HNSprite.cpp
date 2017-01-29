//#include "stdafx.h"
#include "HNSprite.h"
#include "render/GraphicsUtils.h"
#include "test/WireframeOnOff.h"
#include "cocos2d.h"
USING_NS_CC;

namespace HN {
HNSprite::HNSprite(void) : _drawRect(false) {
    setDrawRect(_drawRect || SPRITE_ONOFF);
}

HNSprite::~HNSprite(void) {}

void HNSprite::onExitTransitionDidStart() {
    Sprite::onExitTransitionDidStart();
    stopAllActions();
    unscheduleAllCallbacks();
}

HNSprite *HNSprite::create(const std::string &filename) {
    HNSprite *sprite = new (std::nothrow) HNSprite();
    if (sprite && sprite->initWithFile(filename)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool HNSprite::initWithFile(const std::string &filename) {
    if (!Sprite::initWithFile(filename)) {
        return false;
    }
    mFilename = filename;
    if (false) {
        drawNode = DrawNode::create();
        addChild(drawNode);
    }
    return true;
}

void HNSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    Sprite::draw(renderer, transform, flags);
    if (_drawRect) {
        _customCommand.init(_globalZOrder + 1);
        _customCommand.func =
            CC_CALLBACK_0(HNSprite::onDrawPrimatives, this, transform, flags);
        renderer->addCommand(&_customCommand);
    }
    if (false) {
        drawNode->clear();
        GraphicsUtils::createDrawNode(this->isIgnoreAnchorPointForPosition(),
                                      this->getAnchorPoint(), this->getPosition(),
                                      this->getContentSize(), this, drawNode);
    }
}

void HNSprite::onDrawPrimatives(const cocos2d::Mat4 &transform,
                                uint32_t flags) {
    GraphicsUtils::drawOutline(this->isIgnoreAnchorPointForPosition(),
                               this->getAnchorPoint(), this->getPosition(),
                               this->getContentSize(), this, transform);
}
}
