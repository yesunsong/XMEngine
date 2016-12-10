//#include "stdafx.h"
#include "ASlider.h"
#include "render/GraphicsUtils.h"

ASlider::ASlider():
    _drawRect(false),
    offsetx(0),
    maskDiff(0) {
    setDrawRect(_drawRect || SLIDER_ONOFF);
    setTouchBegan(false);
    setTouchMoved(false);
    setTouchEnded(false);
}

ASlider::~ASlider() {
}

ASlider* ASlider::create(const char* bgFile, const char* progressFile, const char* thumbFile) {
    return ASlider::create(Sprite::create(bgFile), Sprite::create(progressFile), Sprite::create(thumbFile));
}

ASlider* ASlider::create(Sprite * backgroundSprite, Sprite* pogressSprite, Sprite* thumbSprite) {
    ASlider *pRet = new (std::nothrow) ASlider();
    pRet->initWithSprites(backgroundSprite, pogressSprite, thumbSprite);
    pRet->autorelease();
    return pRet;
}

bool ASlider::initWithSprites(Sprite * backgroundSprite, Sprite* progressSprite, Sprite* thumbSprite) {
    if (ControlSlider::initWithSprites(backgroundSprite, progressSprite, thumbSprite)) {
        setOffsetX(offsetx);
        return true;
    }
    return false;
}

bool ASlider::onTouchBegan(Touch* touch, Event* pEvent) {
    if (!isTouchInside(touch) || !isEnabled() || !isVisible()) {
        return false;
    }

    Vec2 location = locationFromTouch(touch);
    sliderBegan(location);
    return true;
}

void ASlider::onTouchMoved(Touch *pTouch, Event *pEvent) {
    Vec2 location = locationFromTouch(pTouch);
    sliderMoved(location);
}

void ASlider::onTouchEnded(Touch *pTouch, Event *pEvent) {
    sliderEnded(Vec2::ZERO);
}

void ASlider::draw(Renderer *renderer, const Mat4& transform, uint32_t flags) {
    if (_drawRect) {
        _customCommand.init(_globalZOrder + 1);
        _customCommand.func = CC_CALLBACK_0(ASlider::onDrawPrimatives, this, transform, flags);
        renderer->addCommand(&_customCommand);
    }

    if (false) {
        //drawNode->clear();
        //GraphicsUtils::createDrawNode2(this->isIgnoreAnchorPointForPosition(), this->getAnchorPoint(), this->getPosition(), this->getContentSize(), this, drawNode);
    }
}

void ASlider::onDrawPrimatives(const cocos2d::Mat4 &transform, uint32_t flags) {
    GraphicsUtils::drawOutline(this->isIgnoreAnchorPointForPosition(), this->getAnchorPoint(), this->getPosition(), this->getContentSize(), this, transform);
}

void ASlider::sliderBegan(Vec2 location) {
    setTouchBegan(true);
    setTouchMoved(false);
    setTouchEnded(false);
    this->setSelected(true);
    getThumbSprite()->setVisible(false);
    getSelectedThumbSprite()->setVisible(true);
    setValue(valueForLocation(location));
}

void ASlider::sliderMoved(Vec2 location) {
    setTouchBegan(false);
    setTouchMoved(true);
    setTouchEnded(false);
    setValue(valueForLocation(location));
}

void ASlider::sliderEnded(Vec2 location) {
    setTouchBegan(false);
    setTouchMoved(false);
    setTouchEnded(true);
    if (this->isSelected()) {
        float scale = getBackgroundSprite()->getContentSize().width/realWidth;
        setValue(valueForLocation(getThumbSprite()->getPosition()*scale));
    }
    getThumbSprite()->setVisible(true);
    getSelectedThumbSprite()->setVisible(false);
    if (callback) {
        callback();
    }
    this->setSelected(false);
}

float ASlider::valueForLocation(Vec2 location) {
    float percent = location.x / getBackgroundSprite()->getContentSize().width;
    return MAX(MIN(_minimumValue + percent * (_maximumValue - _minimumValue), _maximumAllowedValue), _minimumAllowedValue);
}

void ASlider::needsLayout() {
    if (nullptr == getThumbSprite() || nullptr == getSelectedThumbSprite() || nullptr == getBackgroundSprite() || nullptr == getProgressSprite()) {
        return;
    }
    // Update thumb position for new value
    float percent = (_value - _minimumValue) / (_maximumValue - _minimumValue);

    Vec2 pos = getThumbSprite()->getPosition();
    pos.x = percent * realWidth ;
    getThumbSprite()->setPosition(pos);

    getSelectedThumbSprite()->setPosition(pos);

    // Stretches content proportional to newLevel
    Rect textureRect = getProgressSprite()->getTextureRect();
    textureRect = Rect(textureRect.origin.x, textureRect.origin.y, pos.x + maskDiff, textureRect.size.height);
    getProgressSprite()->setTextureRect(textureRect, getProgressSprite()->isTextureRectRotated(), textureRect.size);
}

void ASlider::setSliderEndedCallback(SliderEndedCallback callback) {
    this->callback = callback;
}



//val：百分比
void ASlider::setValue(float val) {
    ControlSlider::setValue(val);
}

//负值是往里，正值是往外
void ASlider::setOffsetX(float offset) {
    getThumbSprite()->setAnchorPoint(Vec2(offset / getThumbSprite()->getContentSize().width, 0.5f));
    getSelectedThumbSprite()->setAnchorPoint(Vec2(offset / getThumbSprite()->getContentSize().width, 0.5f));
    realWidth = getBackgroundSprite()->getContentSize().width - getThumbSprite()->getContentSize().width + offset * 2;
}

void ASlider::setMaskDiff(float value) {
    this->maskDiff = value;
}

void ASlider::setProgressSpritePosition(Vec2 pos) {
    getProgressSprite()->setPosition(pos);
}

void ASlider::setProgressSpritePositionX(float x) {
    getProgressSprite()->setPositionX(x);
}

void ASlider::setProgressSpritePositionY(float y) {
    getProgressSprite()->setPositionY(y);
}
