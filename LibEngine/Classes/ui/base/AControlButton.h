#ifndef __H_AControlButton_H__
#define __H_AControlButton_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"
USING_NS_CC;
using namespace cocos2d::extension;

namespace HN {
class AControlButton :public ControlButton {
public:
    AControlButton();
    virtual ~AControlButton();
    static AControlButton* create();
    static AControlButton* create(cocos2d::ui::Scale9Sprite* sprite);
    static AControlButton* create(const char* filename);

    static AControlButton* create(Node* label, cocos2d::ui::Scale9Sprite* backgroundSprite);
    static AControlButton* create(const std::string& title, const std::string& fontName, float fontSize);
    CC_SYNTHESIZE(bool, _drawRect, DrawRect);

public:
    virtual bool initWithBackgroundSprite(cocos2d::ui::Scale9Sprite* sprite);
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);

    void setGray(bool isGray);
    void setTitle(const char* filename);

    void setTitleOffset(Vec2 off);
private:
    void gray();
    void recovery();

    CustomCommand _customCommand;
    void onDrawPrimatives(const cocos2d::Mat4 &transform, uint32_t flags);
private:
    Sprite* _title;
};
}

#endif //__H_AControlButton_H__