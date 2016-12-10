#ifndef __ASLIDER_H__
#define  __ASLIDER_H__
#include "cocos2d.h"
#include "extensions/cocos-ext.h"

#include "test/WireframeOnOff.h"

USING_NS_CC;
using namespace extension;
using namespace HN;

class ASlider:public ControlSlider {
    typedef std::function<void()> SliderEndedCallback;
public:
    ASlider();
    virtual ~ASlider();
    static ASlider* create(const char* bgFile, const char* progressFile, const char* thumbFile);
    static ASlider* create(Sprite * backgroundSprite, Sprite* pogressSprite, Sprite* thumbSprite);
    virtual bool initWithSprites(Sprite * backgroundSprite, Sprite* progressSprite, Sprite* thumbSprite)override;

    void sliderBegan(Vec2 location);
    void sliderMoved(Vec2 location);
    void sliderEnded(Vec2 location);

    virtual bool onTouchBegan(Touch* touch, Event* pEvent) override;
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent) override;

    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags)override;

    float valueForLocation(Vec2 location);
    void setOffsetX(float offset);
    void setMaskDiff(float value);
    void setProgressSpritePosition(Vec2 pos);
    void setProgressSpritePositionX(float x);
    void setProgressSpritePositionY(float y);
    virtual void setValue(float val)override;
    virtual  void needsLayout()override;

    float maskDiff;

    void setSliderEndedCallback(SliderEndedCallback callback);
    CC_SYNTHESIZE(bool, isTouchBegan, TouchBegan);
    CC_SYNTHESIZE(bool, isTouchMoved, TouchMoved);
    CC_SYNTHESIZE(bool, isTouchEnded, TouchEnded);
private:
    CustomCommand _customCommand;
    void onDrawPrimatives(const cocos2d::Mat4 &transform, uint32_t flags);

private:
    SliderEndedCallback callback;
    float realWidth;
    float offsetx;
    CC_SYNTHESIZE(bool, _drawRect, DrawRect);

};
#endif // __ASLIDER_H__