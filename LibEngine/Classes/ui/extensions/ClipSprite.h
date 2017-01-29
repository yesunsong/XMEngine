/****************************************************************************
圆角精灵（有锯齿，通过覆盖圆角框来解决）
****************************************************************************/

#ifndef CLIP_SPRITE_H
#define CLIP_SPRITE_H

#include "cocos2d.h"
#include "ui/base/HNSprite.h"
USING_NS_CC;
using namespace HN;

class ClipSprite:public Node {
    CC_SYNTHESIZE(HNSprite*, content, ContentSprite);
    CC_SYNTHESIZE(HNSprite*, maskSprite, MaskSprite);
    CC_SYNTHESIZE(bool, _drawRect, DrawRect);

public:
    ClipSprite();
    ~ClipSprite();
    CREATE_FUNC(ClipSprite);
    static ClipSprite* create(const char* filename,const char* stencil);
    virtual bool init()override;

    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags)override;
public:
    void addChildToContent(Node* node);
    void addChildToStencil(Node* node);
    void setInverted(bool inverted);

private:
    Node* _stencil;
    ClippingNode* clippingNode;

    CustomCommand _customCommand;
    void onDrawPrimatives(const cocos2d::Mat4 &transform, uint32_t flags);
private:
    bool init(const char* filename, const char* stencil);
    void initCommon();
};
#endif //CLIP_SPRITE_H