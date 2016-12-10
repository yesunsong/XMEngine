//#include "stdafx.h"
#include "ClipSprite.h"
#include "test/WireframeOnOff.h"
#include "render/GraphicsUtils.h"

ClipSprite::ClipSprite():
    _drawRect(false) {
    setDrawRect(_drawRect || SPRITE_ONOFF);
}

ClipSprite::~ClipSprite() {
}

ClipSprite* ClipSprite::create(const char* filename, const char* stencil) {
    ClipSprite* pRet = new ClipSprite();
    if (pRet&&pRet->init(filename, stencil)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

bool ClipSprite::init(const char* filename, const char* stencil) {
    if (!Node::init()) {
        return false;
    }
    initCommon();

    content = HNSprite::create(filename);
    maskSprite = HNSprite::create(stencil);
    setContentSize(content->getContentSize());

    _stencil->addChild(maskSprite);
    clippingNode->addChild(content);
    return true;
}

bool ClipSprite::init() {
    if (!Node::init()) {
        return false;
    }
    initCommon();
    return true;
}

void ClipSprite::initCommon() {
    _stencil = Node::create();
    clippingNode = ClippingNode::create();
    clippingNode->setStencil(_stencil);
    clippingNode->setAlphaThreshold(0);
    this->addChild(clippingNode);
}

void ClipSprite::addChildToContent(Node* node) {
    clippingNode->addChild(node);
}

void ClipSprite::addChildToStencil(Node* node) {
    _stencil->addChild(node);
}

void ClipSprite::setInverted(bool inverted) {
    clippingNode->setInverted(inverted);
}

void ClipSprite::draw(Renderer *renderer, const Mat4& transform, uint32_t flags) {
    if (_drawRect) {
        _customCommand.init(_globalZOrder + 1);
        _customCommand.func = CC_CALLBACK_0(ClipSprite::onDrawPrimatives, this, transform, flags);
        renderer->addCommand(&_customCommand);
    }
}

void ClipSprite::onDrawPrimatives(const cocos2d::Mat4 &transform, uint32_t flags) {
    GraphicsUtils::drawOutline(this->isIgnoreAnchorPointForPosition(), this->getAnchorPoint(), this->getPosition(), this->getContentSize(), this, transform);
}
